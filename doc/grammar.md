# Grammar

The specification of the Hudson programming language in EBNF notation is the following :

```ebnf
program         =   { stmt }
stmt            =   expr_stmt       |   declaration         |   assignment  |   inc_dec |   return     
                |   break           |   continue            |   print       |   block   |   while             
                |   for             |   if                  |   function    |   import
expr_stmt       =   expr ";"
declaration     =   type ident [ "=" expr ] ";"
assignment      =   ident ( "=" | "+=" | "+-" | "*=" |  "%=" | "/+" ) expr ";"
inc_dec         =   ident ( "++" | "--" ) ";"
return          =   "return" [ expr ] ";"
break           =   "break" ";"
continue        =   "continue" ";"
print           =   "print" "(" [ expr ] ")" ";"
block           =   "{" { stmt } "}"
while           =   "while" "(" expr ")" ( stmt | ";" )
for             =   "for" "(" [ declaration | assignment ] ";" expr ";" assignment | inc_dec ")" ( smt | ";" )
if              =   "if" "(" expr ")" stmt [ "else" stmt ]
function        =   "fnc" ident fnc_signature block
import          =   "import" string_lit ";"
expr            =   or
or              =   and { "||" and }
and             =   bitwise_or { "&&" bitwise_or }
bitwise_or      =   bitwise_xor { "|"  bitwise_xor  }
bitwise_xor     =   bitwise_and { "^" bitwise_and }
bitwise_and     =   equality { "&" equality }
equality        =   comparison { "==" | "!=" comparison }
comparison      =   bitshift { "<" | "<=" | ">" | ">=" bitshift }
bitshift        =   term { ">>" | "<<" term }
term            =   factor { "-" | "+" factor }
factor          =   unary { "/" | "*" | "%" unary }
unary           =   ( "+" | "-" | "!" | "~" ) unary | call
call            =   primary { "(" [ params ] ")" }
primary         =   int_lit | ident | string_lit | anonymous_fnc | grouping
grouping        =   "(" expr ")"

params          =   expr { "," expr }
anonymous_fnc   =   'fnc' fnc_signature block
fnc_signature   =   "(" [ ident type { "," ident type } ] ")" [ type ]
type            =   "int" | "str" | "fnc" | fnc_signature
ident           =   ( letter | "_" ) { letter | digit | "_" }
int_lit         =   digit | { digit }
string_lit      =   '"' { * } '"'   
letter          =   "A" ... " Z" | "a" ... "z"
digit           =   "0" ... "9"
```