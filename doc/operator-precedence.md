
```
expression  -> or
or          -> and (( '||' ) and ) *
and         -> bitwise_or (( '&&' ) bitwise_or ) *
bitwise_or  -> bitwise_xor (( '|' ) bitwise_xor ) *
bitwise_xor -> bitwise_and (( '^' ) bitwise_and ) *
bitwise_and -> equality (( '&' ) equality ) *
equality    -> comparison (( '==' | '!=' ) comparison ) *
comparison  -> bitshift (( '<' | '<=' | '>' | '>=' ) bitshift ) *
bitshift    -> term (( '>>' | '<<' ) term ) *
term        -> factor ( ( '-' | '+' ) factor ) *
factor      -> unary ( ( '/' | '*' | '%' ) unary ) *
unary       -> ( '+' | '-' ) unary | primary
primary     -> Number | '(' expression ')'
```