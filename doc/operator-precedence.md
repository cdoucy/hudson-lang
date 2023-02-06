
```
expression  -> or
or          -> and (( '||' ) and ) *
and         -> equality (( '&&' ) equality ) *
equality    -> comparison (( '==' | '!=' ) comparison ) *
comparison  -> term (( '<' | '<=' | '>' | '>=' ) term ) *
term        -> factor ( ( '-' | '+' ) factor ) *
factor      -> unary ( ( '/' | '*' | '%' ) unary ) *
unary       -> ( '+' | '-' ) unary | primary
primary     -> Number | '(' expression ')'
```