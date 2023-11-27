from tokenizer import *
from enums import *
import shlex
import re


class VM:

    def __init__(self):
        self.sp = 8192
        self.local = 8196
        self.argument = 8200
        self.temp = 8204
        self.this = 8208
        self.that = 8212
        self.data_seg=8216
        
        self.num_local = 0
        self.num_temp = 0
        
        self.translated_code = ".section\n.text\njal main\n"
        self.data_segment = ".section\n.data\n"
        
        self.label_index=0
        self.data_segment_start = 0x10010000
        self.data_segment_dict = {}


    #label L1
    def label(self, line):
        self.translated_code += f"{line[-1]}:\n"

    #get temporary variables for branching instructions
    def get_new_label(self):
        label = 'custom_label'+str(self.label_index)
        self.label_index += 1
        return label

    #goto L1
    def goto(self, line):
        self.translated_code += f"j {line[-1]}\n"


    #possible types of stmts
    #push local 1 INT
    #push constant 'a' CHAR
    #push constant false BOOL
    def push(self, line):

        segment=line[1]
        datatype= line[-1]
        index=0

        if(segment != Segment.constant.value):
            index = int(line[2])
        else:
            if (datatype == Datatypes.INT.value or datatype == Datatypes.BOOL.value):
                index = int(line[2])
            elif (datatype == Datatypes.CHAR.value):
                if (segment == Segment.constant.value):
                    index = ord(line[2]) 
                else:
                    index = int(line[2])
            elif (datatype == Datatypes.STR.value):
                index = int(line[2])

            # print("ayyein.............",index)
        if (segment == Segment.data.value):
            
            pointer=self.data_seg
            #push data 0 "sth" STR
            if (len(line) == 5):
                #push to data segment and the .data section
                string_val = '"'+line[-2]+'"'
                var = f"__{self.cur_function}__data{index}"
                
                string_val = string_val[1:-1].replace("\\/", "/").encode().decode('unicode_escape')
                length = len(string_val)
                self.data_segment_dict[var] = [
                    ".asciiz", 
                    line[-2], 
                    self.data_segment_start, 
                    length]
                
                self.data_segment_start += length+1

                # push to data segment first
                self.translated_code+=f"lw $t1, {(var)}\n" #la load address should be here ideally
                self.translated_code+=f"addi $t0, $zero, {(pointer)}\n"
                self.translated_code+=f"add $t0, $t0, $fp\n"
                self.translated_code+=f"lw $t0, 0(t0)\n"
                self.translated_code+=f"addi $t0, $t0, {(index*4+4)}\n"
                self.translated_code+=f"sw $t1, 0($t0)\n"

                #now push to stack as well
                self.translated_code+=f"sw $t1 0($sp)\n"
                self.translated_code += f"addi $sp, $sp, 4\n"


            else:
                self.translated_code+=f"addi $t0, $zero, {(pointer)}\n"
                self.translated_code+=f"add $t0, $t0, $fp\n"
                self.translated_code+=f"lw $t0, 0($t0)\n"
                self.translated_code+=f"addi $t0, $t0, {(index*4+4)}\n"

                self.translated_code+=f"sw $t0 0($sp)"
                self.translated_code += f"addi $sp, $sp, 4\n"

        # address: if (segment == Segment.data.value): i.e. the type
        # push data 0 "enter factorial: " STR
           


        #look: that segment, $fp
        if(segment != Segment.constant.value and segment != Segment.that.value):
            pointer = None
            if (segment == Segment.local.value):
                pointer = self.local
            elif (segment == Segment.temp.value):
                pointer = self.temp
            elif (segment == Segment.argument.value):
                pointer = self.argument

            if (datatype == Datatypes.INT.value):

                self.translated_code += f"addi $t0, $zero, {(pointer)}\n"
                self.translated_code += f"add $t0, $t0, $fp\n"
                self.translated_code += f"lw $t0, 0($t0)\n"

                self.translated_code += f"addi $t0, $t0, {(index*4+4)}\n"
                self.translated_code += f"lw $t0, 0($t0)\n"
                self.translated_code += f"sw $t0, 0($sp)\n"
                self.translated_code += f"addi $sp, $sp, 4\n"

            elif (datatype == Datatypes.CHAR.value or datatype == Datatypes.BOOL.value):
                self.translated_code += f"addi $t0, $zero, {(pointer)}\n"
                self.translated_code += f"add $t0, $t0, $fp\n"
                self.translated_code += f"lw $t0, 0($t0)\n"

                self.translated_code += f"addi $t0, $t0, {(index*4+4)}\n"
                self.translated_code += f"lw $t0, 0($t0)\n"
                self.translated_code += f"sw $t0, 0($sp)\n"
                self.translated_code += f"addi $sp, $sp, 4\n"

        elif (segment == Segment.constant.value):
            constant = index
            if (datatype == Datatypes.INT.value or datatype == Datatypes.CHAR.value):
                self.translated_code += f"addi $t0, $zero, {constant}\n"
                self.translated_code += f"sw $t0, 0($sp)\n"
                self.translated_code += f"addi $sp, $sp, 4\n"

            #helps later on in adding INT + CHAR types, soinstead of true/ false we push 1/0
            elif (datatype == Datatypes.BOOL.value):
                self.translated_code += f"addi $t0, $zero, {1 if line[2]=='true' else 0}\n"
                self.translated_code += f"sw $t0, 0($sp)\n"
                self.translated_code += f"addi $sp, $sp, 4\n"
        
        elif (segment == Segment.that.value): #for arrays
            pointer=self.that
            if (datatype == Datatypes.INT.value):

                self.translated_code += f"addi $t0, $zero, {(pointer)}\n"
                self.translated_code += f"add $t0, $t0, $fp\n"
                self.translated_code += f"lw $t0, 0($t0)\n"

                self.translated_code += f"addi $t0, $t0, {(index*4+4)}\n"
                self.translated_code += f"lw $t0, 0($t0)\n"
                self.translated_code += f"sw $t0, 0($sp)\n"
                self.translated_code += f"addi $sp, $sp, 4\n"

            elif (datatype == Datatypes.CHAR.value or datatype == Datatypes.BOOL.value):
                self.translated_code += f"addi $t0, $zero, {(pointer)}\n"
                self.translated_code += f"add $t0, $t0, $fp\n"
                self.translated_code += f"lw $t0, 0($t0)\n"

                self.translated_code += f"addi $t0, $t0, {(index*4+4)}\n"
                self.translated_code += f"lw $t0, 0($t0)\n"
                self.translated_code += f"sw $t0, 0($sp)\n"
                self.translated_code += f"addi $sp, $sp, 4\n"

        
        #address: what other type of segment could it be; that? org(bbf a1 type)

    #possible types
    #pop local 2 INT
    #pop temp 1 CHAR
    def pop(self, line):
        segment = line[1]
        datatype = line[-1]
        index = int(line[2])

        pointer = None
        if (segment == Segment.local.value):
            pointer = self.local
        elif (segment == Segment.temp.value):
            pointer = self.temp
        elif (segment == Segment.argument.value):
            pointer = self.argument
        elif (segment== Segment.data.value):
            pointer=self.data_seg
        elif (segment== Segment.that.value):
            pointer=self.that

        #address: org(bee a1 type); for 'that'

        if (datatype == Datatypes.INT.value or datatype == Datatypes.CHAR.value or datatype == Datatypes.BOOL.value):
            self.translated_code += f"addi $sp, $sp, -4\n"
            self.translated_code += f"lw $t0, 0($sp)\n"

            self.translated_code += f"addi $t1, $zero, {pointer}\n"
            self.translated_code += f"add $t1, $t1, $fp\n"
            self.translated_code += f"lw $t1, 0($t1)\n"

            self.translated_code += f"addi $t1, $t1, {(index*4+4)}\n"
            self.translated_code += f"sw $t0, 0($t1)\n"

        if(line[0]== 'combined'): #the optimized code
            self.translated_code+=f"addi $sp, $sp, 4\n"

    #possible types:
    #Add/Sub/LShift/RShift/BitAnd/BitOr/BitXor INT
    def Operator(self, line):
        datatype = line[-1]
        operator = line[0]
        # print("check................... "+operator+" "+datatype)
        instruction = ''
        if (operator == Instructions.Add.value):
            instruction = Operators.Add.value
        elif (operator == Instructions.Sub.value):
            instruction = Operators.Sub.value
        elif (operator == Instructions.LShift.value):
            instruction = Operators.LShift.value
        elif (operator == Instructions.RShift.value):
            instruction = Operators.RShift.value
        elif (operator == Instructions.BitAnd.value):
            instruction = Operators.BitAnd.value
        elif (operator == Instructions.BitOr.value):
            instruction = Operators.BitOr.value
        elif (operator == Instructions.BitXor.value):
            instruction = Operators.BitXor.value
        elif (operator == Instructions.mac.value):
            instruction = Operators.mac.value

        if(instruction=='mac'):
                self.translated_code += f"addi $sp, $sp, -4\n"
                self.translated_code += f"lw $t0, 0($sp)\n"
                self.translated_code += f"addi $sp, $sp, -4\n"
                self.translated_code += f"lw $t1, 0($sp)\n"
                self.translated_code += f"mac $t1, $t0\n"
            
        else:
            if (datatype == Datatypes.INT.value or datatype == Datatypes.CHAR.value or datatype == Datatypes.BOOL.value):
                self.translated_code += f"addi $sp, $sp, -4\n"
                self.translated_code += f"lw $t0, 0($sp)\n"
                self.translated_code += f"addi $sp, $sp, -4\n"
                self.translated_code += f"lw $t1, 0($sp)\n"
                self.translated_code += f"{instruction} $t0, $t1, $t0\n"
                self.translated_code += f"sw $t0, 0($sp)\n"
                self.translated_code += f"addi $sp, $sp, 4\n"


    def condition_builtin(self, line):
        datatype = line[-1]
        condition = line[0]
        if (condition == Instructions.Eq.value):
            condition = Operators.Eq
            branch = Operators.Eq.value
        elif (condition == Instructions.Lt.value):
            condition = Operators.Lt
            branch = Operators.Lt.value
        elif (condition == Instructions.Ge.value):
            condition = Operators.Ge
            branch = Operators.Ge.value
        elif (condition == Instructions.Le.value):
            condition = Operators.Le
            branch = Operators.Le.value
        elif (condition == Instructions.Gt.value):
            condition = Operators.Gt
            branch = Operators.Gt.value

        label1 = self.get_new_label()
        label2 = self.get_new_label()

        if (datatype == Datatypes.INT.value or datatype == Datatypes.CHAR.value or datatype == Datatypes.BOOL.value):
            self.translated_code += f"addi $sp, $sp, -4\n"
            self.translated_code += f"lw $t1, 0($sp)\n"  
            self.translated_code += f"addi $sp, $sp, -4\n"
            self.translated_code += f"lw $t0, 0($sp)\n"

            self.translated_code += f"{branch} $t0, $t1, {label1}\n"
            self.translated_code += f"addi $t2, $zero, 0\n"
            self.translated_code += f"j {label2}\n"
            self.translated_code += f"{label1}:  \n"
            self.translated_code += f"addi $t2, $zero, 1\n"
            self.translated_code += f"{label2}:\n"

            # self.translated_code += f"sub $t0, $t0, $t1\n"
            self.translated_code += f"sw $t2, 0($sp)\n"
            self.translated_code += f"addi $sp, $sp, 4\n"            


    #if-goto <some_label>
    def if_goto(self, line):
        label= line[-1]
        self.translated_code += f"addi $sp, $sp, -4\n"
        self.translated_code += f"lw $t0, 0($sp)\n"
        self.translated_code += f"addi $t1, $zero, 1\n"
        self.translated_code += f"beq $t0, $t1, {label}\n"

    def print_stmt(self, line):
        datatype= line[-1]
        if(datatype==Datatypes.STR.value):
            self.translated_code+=f"addi $sp, $sp, -4\n"
            self.translated_code+=f"lw $t0, 0($sp)\n"
            
            
            self.translated_code+= f"loop:\n"
            self.translated_code+= f"lw $t0, 0($t0)\n"
            self.translated_code+= f"beq $t0, $zero, end\n"
            self.translated_code+= f"add $a0, $t0, $zero\n"
            self.translated_code+= f"addi $sp, $sp, 4\n"
            self.translated_code+= f"addi $v0, $zero, 4\n"
            self.translated_code+= f"syscall\n"
            self.translated_code+= f"addi $t0, $t0, 4\n"
            self.translated_code+= f"j loop\n"
            self.translated_code+= f"end:\n"
            self.translated_code+=f"addi $sp, $sp, 4\n"

        else:
            self.translated_code += f"addi $sp, $sp, -4\n"
            self.translated_code += f"lw $t0, 0($sp)\n"
            self.translated_code += f"add $a0, $t0, $zero\n"
            self.translated_code += f"addi $sp, $sp, 4\n"
            self.translated_code += f"addi $v0, $zero, 4\n"
            self.translated_code += f"syscall\n"

    #address: new print stmt

    #call func 2
    def function_call(self, line):
        num_args = int(line[-1])

        if (num_args == 0):
            self.push('push constant 0 INT'.split(' '))

        # storing current arg pointer in $t2 register
        self.translated_code += f"addi $t0, $zero, {self.argument}\n"
        self.translated_code += f"lw $t2, 0($t0)\n"

        # setting arg pointer
        self.translated_code += f"addi $t0, $sp, {-(num_args+1)*4}\n"
        self.translated_code += f"addi $t1, $zero, {self.argument}\n"
        self.translated_code += f"sw $t0, 0($t1)\n"

        # the base addresses for all mem segments are stored on the stack, which is a common way to pass parameters and create a local stack frame for function execution

        self.translated_code += f"addi $t0, $zero, {self.local}\n"
        self.translated_code += f"lw $t1, 0($t0)\n"
        self.translated_code += f"sw $t1, 0($sp)\n"
        self.translated_code += f"addi $sp, $sp, 4\n"

        self.translated_code += f"sw $t2, 0($sp)\n"
        self.translated_code += f"addi $sp, $sp, 4\n"

        self.translated_code += f"addi $t0, $zero, {self.temp}\n"
        self.translated_code += f"lw $t1, 0($t0)\n"
        self.translated_code += f"sw $t1, 0($sp)\n"
        self.translated_code += f"addi $sp, $sp, 4\n"

        self.translated_code += f"addi $t0, $zero, {self.this}\n"
        self.translated_code += f"lw $t1, 0($t0)\n"
        self.translated_code += f"sw $t1, 0($sp)\n"
        self.translated_code += f"addi $sp, $sp, 4\n"

        self.translated_code += f"addi $t0, $zero, {self.that}\n"
        self.translated_code += f"lw $t1, 0($t0)\n"
        self.translated_code += f"sw $t1, 0($sp)\n"
        self.translated_code += f"addi $sp, $sp, 4\n"

        self.translated_code += f"jal {line[1]}\n"
        self.translated_code += f"addi $sp, $sp, -4\n"          
        self.translated_code += f"lw $v1, 0($sp)\n"           
        self.translated_code += f"addi $s0, $v1, $zero\n"           

    # def init_mem(self):
    #     # 8224 to 8735 (512, local)
    #     self.translated_code += f"addi $t0, $zero, 8224\n"
    #     self.translated_code += f"addi $t1, $zero, {self.local}\n"
    #     self.translated_code += f"add $t1, $fp, $t1\n"
    #     self.translated_code += f"sw $t0, 0($t1)\n"

    #     # 8736 to 8767 (32, argument)
    #     self.translated_code += f"addi $t0, $zero, 8736\n"
    #     self.translated_code += f"addi $t1, $zero, {self.argument}\n"
    #     self.translated_code += f"add $t1, $fp, $t1\n"
    #     self.translated_code += f"sw $t0, 0($t1)\n"

    #     # 8768 to 9279 (512, temp)
    #     self.translated_code += f"addi $t0, $zero, 8768\n"
    #     self.translated_code += f"addi $t1, $zero, {self.temp}\n"
    #     self.translated_code += f"add $t1, $fp, $t1\n"
    #     self.translated_code += f"sw $t0, 0($t1)\n"

    #     # 9280 to 10303 (1024, stack)
    #     self.translated_code += f"addi $t0, $zero, 9280\n"
    #     self.translated_code += f"addi $t1, $zero, {self.sp}\n"
    #     self.translated_code += f"add $t1, $fp, $t1\n"
    #     self.translated_code += f"sw $t0, 0($t1)\n"

    #     self.translated_code += f"addi $sp, $zero, 9280\n"
    #     self.translated_code += f"add $sp, $sp, $fp\n\n"
    
    #function mult 2 3 INT
    def function_def(self, line):

        self.num_local = int(line[-3])
        self.num_temp = int(line[-2])
        function = line[1]
        self.cur_function = function
        if (function == 'main'):
            self.translated_code += f"{function}:\n"
            # self.init_mem()
            return

        self.translated_code += f"{function}:\n"
        
        # storing return address
        self.translated_code += f"sw $ra, 0($sp)\n"
        self.translated_code += f"addi $sp, $sp, 4\n"

        # setting new local
        self.translated_code += f"addi $t0, $zero, {self.local}\n"
        self.translated_code += f"sw $sp, 0($t0)\n"

        # setting new temp
        self.translated_code += f"addi $t1, $sp, {self.num_local*4}\n"
        self.translated_code += f"addi $t0, $zero, {self.temp}\n"
        self.translated_code += f"sw $sp, 0($t0)\n"

        # setting new working stack
        self.translated_code += f"addi $sp, $sp, {(self.num_temp+self.num_local)*4}\n"

    def return_call(self, line):

        if (self.cur_function == 'main'):
            self.translated_code += f"j __END__\n" #address: do we need jal here?
            return

        self.translated_code += f"addi $sp, $sp, -4\n"
        self.translated_code += f"lw $t0, 0($sp)\n"
        self.translated_code += f"addi $t1, $zero, {self.argument}\n"
        self.translated_code += f"lw $t1, 0($t1)\n"
        self.translated_code += f"sw $t0, 0($t1)\n"

        # self.translated_code += f"addi $sp, $sp, {(self.num_local+self.num_temp)*4}\n"
        self.translated_code += f"addi $t0, $zero, {self.local}\n"
        self.translated_code += f"lw $sp, 0($t0)\n"

        self.translated_code += f"lw $t0, -8($sp)\n"
        self.translated_code += f"addi $t1, $zero, {self.that}\n"
        self.translated_code += f"sw $t0, 0($t1)\n"

        self.translated_code += f"lw $t0, -12($sp)\n"
        self.translated_code += f"addi $t1, $zero, {self.this}\n"
        self.translated_code += f"sw $t0, 0($t1)\n"

        self.translated_code += f"lw $t0, -16($sp)\n"
        self.translated_code += f"addi $t1, $zero, {self.temp}\n"
        self.translated_code += f"sw $t0, 0($t1)\n"

        self.translated_code += f"lw $t2, -20($sp)\n"
        # self.translated_code += f"addi $t1, $zero, -{self.argument}\n"
        # self.translated_code += f"sw $t0, 0($t1)\n"

        self.translated_code += f"lw $t0, -24($sp)\n"
        self.translated_code += f"addi $t1, $zero, {self.local}\n"
        self.translated_code += f"sw $t0, 0($t1)\n"

        self.translated_code += f"lw $t0, -4($sp)\n"

        self.translated_code += f"addi $t1, $zero, {self.argument}\n"
        self.translated_code += f"lw $sp, 0($t1)\n"

        self.translated_code += f"addi $sp, $sp, 4\n"

        # self.translated_code += f"lw $t0, 20($sp)\n"
        self.translated_code += f"addi $t1, $zero, {self.argument}\n"
        self.translated_code += f"sw $t2, 0($t1)\n"

        self.translated_code += f"jal $ra\n"
        

    def scan(self, line):
        datatype=line[-1]
        if (datatype == Datatypes.INT.value):
            self.translated_code += "addi $v0, $zero, 5\nsyscall\n"
            self.translated_code += f"sw $a0, 0($sp)\n"

        self.translated_code += f"addi $sp, $sp, 4\n"
        self.pop(f"pop {line[1]} {line[2]} {line[3]}".split(' '))

    def generate_target_code(self, vm_code):

        preprocess = Preprocess()
        vm_code = preprocess.preprocess(vm_code)

        for line in vm_code.splitlines():
            # print(line)
            line = shlex.split(line)
            if (len(line) == 0):
                continue
            
            if (line[0] == Instructions.Add.value or line[0] == Instructions.Sub.value or line[0] == Instructions.BitAnd.value or
                    line[0] == Instructions.BitOr.value or line[0] == Instructions.BitXor.value or line[0] == Instructions.LShift.value or
                    line[0] == Instructions.RShift.value or line[0] == Instructions.mac.value):
                self.Operator(line)
            elif (line[0] == Instructions.Eq.value or line[0] == Instructions.Lt.value or line[0] == Instructions.Ge.value or line[0] == Instructions.Le.value or line[0] == Instructions.Gt.value):
                self.condition_builtin(line)
            elif (line[0] == Instructions.push.value):
                self.push(line)
            elif (line[0] == Instructions.pop.value or line[0] == 'combined'):
                self.pop(line)
            elif (line[0] == Instructions.function.value):
                self.function_def(line)
            elif (line[0] == Instructions.ret.value):
                self.return_call(line)
            elif (line[0] == Instructions.if_goto.value):
                self.if_goto(line)
            elif (line[0] == Instructions.goto.value):
                self.goto(line)
            elif (line[0] == Instructions.label.value):
                self.label(line)
            elif (line[0] == Instructions.print_stmt.value):
                self.print_stmt(line)
            elif (line[0] == Instructions.call.value):
                self.function_call(line)
            elif (line[0] == Instructions.scan.value):
                self.scan(line)
            elif(line[0] == 'MAC'):
                self.translated_code+=f"addi $s1, $zero, 0\n"

        #some postprocessing
        # self.translated_code = self.postprocess(self.translated_code)
        self.translated_code+=f"__END__:\n"
        self.translated_code+=f"nop\n"

        final_asm_code = ''
        enable = False
        sth_temp=self.translated_code
        for line in sth_temp.splitlines():
            if ('.text' in line):
                enable = True
            if (enable):
                final_asm_code += re.sub(r', ', ',', line)
            final_asm_code += '\n'

        final_asm_code = re.sub(r'\n\n', '\n', final_asm_code)

        final_code=''
        for line in final_asm_code.splitlines():
            if('0x' in line):
                hex_val=line.split('0x')[-1]
                int_val=int(hex_val,16)
                final_code+=f"{line.split('0x')[0]}{int_val}\n"
            else:
                final_code+=f"{line}\n"

        self.translated_code =f".section"+final_code

        sorted_list = sorted(
            self.data_segment_dict.items(), key=lambda x: x[1][2])
        
        # print(self.data_segment_dict.values())
        # print("heyyyyyy")
        for var, (type, value, _, __) in sorted_list:
            # print(type)
            self.data_segment += f"{var}:\n\t{type} \"{value}\"\n"

        final_code = self.data_segment + self.translated_code
        return final_code


#address: address these parts later
#look: use case?

#$fp: is it a frame pointer like, if accessing a particular index and then like an offset add this $fp then access base address valuein that location