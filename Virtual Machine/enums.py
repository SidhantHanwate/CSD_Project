import enum

class Instructions(enum.Enum):
    push = 'push'
    pop = 'pop'
    function = 'function'
    label = 'label'
    goto = 'goto'
    ret = 'return'
    if_goto = 'if-goto'
    print_stmt = 'print'
    call = 'call'
    scan = 'scan'

    Eq = 'eq'
    Lt = 'lt'
    Gt = 'gt'
    Ge = 'ge'
    Le = 'le'
    Neq = 'neq'
    Not = 'not'

    Add = 'add'
    Sub = 'sub'
    LShift = 'lshift'
    RShift = 'rshift'
    BitAnd = 'and'
    BitOr = 'or'
    BitXor = 'xor'
    mac='mac'


class Segment(enum.Enum):
    local = 'local'
    argument = 'argument'
    constant = 'constant'
    temp = 'temp'
    that = 'that'
    data = 'data'


class Datatypes(enum.Enum):
    INT = 'INT'
    BOOL = 'BOOL'
    CHAR = 'CHAR'
    STR = 'STRING'


class Operators(enum.Enum):
    Add = 'add'
    Sub = 'sub'
    LShift = 'sll'
    RShift = 'srl'
    BitAnd = 'and'
    BitOr = 'or'
    BitXor = 'xor'
    mac='mac'

    Plus = '+'
    Minus = '-'
    Mul = '*'
    Div = '/'
    Mod = '%'

    LeftShift = '<<'
    RightShift = '>>'
    LogicalAnd = '&&'
    LogicalOr = '||'
    Gt = 'bgt'
    Lt = 'blt'
    Ge = 'bge'
    Le = 'ble'
    Eq = 'beq'
