
```
program                 -> statement* EOF
statement               -> expressionStatement | declarationStatement | assignmentStatement | incDecStatement | returnStatement | breakStatement | continueStatement | print | block | while | for | if | function
expressionStatement     -> expression ';'
declarationStatement    -> declaration ';'
assignementStatement    -> assignement ';'
incDecStatement         -> incDec ';'
returnStatement         -> return (expression)? ';'
breakStatement          -> break ';'
continueStatement       -> continue ';'
declaration             -> Type Identifier ('=' expression)?
assignment              -> Identifier assimentOperator expression
assignmentOperator      -> '=' | '+= | '+-' | '*=' | '%=' | '/='
incDec                  -> Identifier ('++' | '--')
print                   -> 'print('expression?')' ';'
block                   -> '{' statement* '}'
while                   -> 'while' '(' expression ')' (statement | ';' )
for                     -> 'for' '(' (initStatement)? ';' expression ';' (stepStatement)? ')' (statement | ';')
initStatement           -> declaration | assignment
stepStatement           -> assignement | incDec
if                      -> 'if' '(' expression ')' statement ('else' statement)?
function                -> 'fnc' Identifier FunctionSignature block
expression              -> or
or                      -> and (( '||' ) and ) *
and                     -> bitwise_or (( '&&' ) bitwise_or ) *
bitwise_or              -> bitwise_xor (( '|' ) bitwise_xor ) *
bitwise_xor             -> bitwise_and (( '^' ) bitwise_and ) *
bitwise_and             -> equality (( '&' ) equality ) *
equality                -> comparison (( '==' | '!=' ) comparison ) *
comparison              -> bitshift (( '<' | '<=' | '>' | '>=' ) bitshift ) *
bitshift                -> term (( '>>' | '<<' ) term ) *
term                    -> factor ( ( '-' | '+' ) factor ) *
factor                  -> unary ( ( '/' | '*' | '%' ) unary ) *
unary                   -> ( '+' | '-' | '!' | '~' ) unary | call
call                    -> primary ( '(' params? ')' )*
params                  -> expression ( ',' expression )*
primary                 -> Integer | Identifier | String | AnonymousFunction | grouping
grouping                -> '(' expression ')'

Integer                 -> ['0'-'9']+
Identifier              -> [a-zA-Z_][a-zA-Z_0-9]*
String                  -> "*"
AnonymousFunction       -> 'fnc' FunctionSignature block
Type                    -> 'int' | 'str' | 'fnc' FunctionSignature
FunctionSignature       -> FunctionParams (Type)?
FunctionParams          -> '(' ( TypeIdent ( ',' TypeIdent)* )?  ')'
TypeIdent               -> Identifier Type
```