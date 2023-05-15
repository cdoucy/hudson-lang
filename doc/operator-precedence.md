
```
program                 -> statement* EOF
statement               -> expressionStatement | declaration | assignment
expressionStatement     -> expression ';'
declaration             -> Type Identifier ('=' expression)? ';'
assignment              -> Identifier '=' expression ';'
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