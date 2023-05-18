
```
program                 -> statement* EOF
statement               -> expressionStatement | declaration | assignment | print | block | while | for | if
expressionStatement     -> expression ';'
declaration             -> Type Identifier ('=' expression)? ';'
assignment              -> Identifier '=' expression ';'
print                   -> 'print('expression?')' ';'
block                   -> '{' statement* '}'
while                   -> 'while' '(' expression ')' (statement | ';' )
for                     -> 'for' '(' (declaration | assignment) | ';' expression ';' expression? ')' (statement | ';')
if                      -> 'if' '(' expression ')' statement ('else if' statement)* ('else' statement)?
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
unary                   -> ( '+' | '-' | '!' | '~' ) unary | primary
primary                 -> Integer | Identifier | String | grouping
grouping                -> '(' expression ')'

Integer                 -> ['0'-'9']+
Type                    -> 'int' | 'str'
Identifier              -> [a-zA-Z_][a-zA-Z_0-9]*
String                  -> "*"
```