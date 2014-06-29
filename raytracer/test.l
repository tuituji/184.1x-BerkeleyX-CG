%{

//#define YYSTYPE double
#include "test.yy.hpp"
int line_num = 0;

%}

WHITESPACE [ \t\r]+
NUMBER [-+]?([0-9]+|(([0-9]+\.[0-9]*)|(\.[0-9]+)))([eE][-+]?[0-9]+)?
IDENT [a-zA-Z_][a-zA-Z_0-9]*
%x STR COMMENT INCL INCL_FILE


%%

"#" { BEGIN COMMENT; }
<COMMENT>. /* eat it up */ 
<COMMENT>\n { ++line_num; BEGIN INITIAL; }
{WHITESPACE} /* do nothing */
\n { ++line_num; }

size { return SIZE; }
camera { return CAMERA; }
ambient { return AMBIENT; }
directional { return DIRECTIONAL; }
point { return POINT; }
diffuse { return DIFFUSE; }
specular { return SPECULAR; }
maxverts { return MAXVERTS; }
vertex { return VERTEX; }
tri { return TRI; }
sphere { return SPHERE; }
shiness { return SHINESS; }
plane { return PLANE; }
popTransform {return POP;}
pushTransform {return PUSH;}
translate {return TRANSLATE; }
scale { return SCALE; }

{NUMBER} {
    yylval.num = (float) atof(yytext);
    return NUM;
}

%%

