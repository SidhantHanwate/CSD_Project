import sys
import os
from translator import VM

if __name__ == '__main__':
	script_dir = os.path.dirname(__file__)
	rel_path = sys.argv[1]
	abs_file_path = os.path.join(script_dir, rel_path)
	asm_code = ""
	with open(abs_file_path, 'r') as file:
		lines=file.readlines()
	
	modified_lines = []
	i = 0
	while i < len(lines):
		if i < len(lines) - 1 and lines[i].startswith("pop") and lines[i + 1].startswith("push"):
			pop_parts = lines[i].split()
			push_parts = lines[i + 1].split()
			if len(pop_parts) == len(push_parts) and pop_parts[1:] == push_parts[1:]:
				combined_line = "combined" + lines[i][3:]
				modified_lines.append(combined_line)
				i += 2
			else:
				modified_lines.append(lines[i])
				i += 1
		else:
			modified_lines.append(lines[i])
			i += 1
		
	output_file_path = os.path.join(script_dir, 'input/newfile.vm')
	with open(output_file_path, 'w') as output_file:
		output_file.writelines(modified_lines)

	with open(output_file_path) as file:
		vm_code = file.read()

		# asm_generator = VM()
		asm_generator = VM()
		# starting point of the virtual machine
		asm_code = asm_generator.generate_target_code(vm_code)

	script_dir = os.path.dirname(__file__)
	rel_path = f'output/asm.asm'
	abs_file_path = os.path.join(script_dir, rel_path)

	with open(abs_file_path, 'w+') as file:
		file.write(asm_code)
