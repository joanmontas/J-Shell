# J-Shell

# Grammar
        Program    := <commands>+ ;
        commands   := <ident | args> <args>;
                   |  <ident | path> <args> <bin> <ident | path> <args>
        <bin>      := '|" | ">" | "<" | ">>" | "<<"
        <args>     := (<terminal>)*
        <terminal> := <ident | string | path>
        <ident>    := []+
        <string>   := "[]*"
        <path>     := .[]* | /[]*