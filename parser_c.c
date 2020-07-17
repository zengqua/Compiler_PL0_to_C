#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"

int getNextToken();

void vardeclaration(FILE* ofp);

void procedureprocess(FILE* ofp);

void beginprocess(FILE* ofp);

void writeprocess(FILE* ofp);

void readprocess(FILE* ofp);

void symprocess(FILE* ofp);

void ifprocess(FILE* ofp);

void whileprocess(FILE* ofp);

void callprocess(FILE* ofp);

void epression(FILE* ofp);

int num = 0, lexemeListIndex = 0;
int lev = 0;
int semi = 0;
int token = 0;
int qui = 0;
char id[12];
char codeline[10][2000];
int index = 0;
int vari = 0;
int whilei = 0;

void parser(void)
{
	FILE* ifp;
	FILE* ofp;

	ifp = fopen("lexoutput.txt", "r");
	ofp = fopen("parserout.c", "w");

	int i;

	 //Lexigraphical level
	int dx = 0; //data index
	int tx = 0; //table index

	token = 0;
	strcat(codeline[0], "#include <stdio.h>\n");
	while (token != 19)
	//for (i = 0; i < 12; i++)
	{
		epression(ofp);
	}
	for (int j = 0; j < 10; j++)
	{
		fprintf(ofp, "%s", codeline[j]);
	}
	
	//}
	//fprintf(ofp, "hello\n");
	fclose(ifp);
	fclose(ofp);
}

int getNextToken() {

	token = lexList[lexemeListIndex].tokenID;

	//Takes care of variables, always represented by "2 | variable"
	if (token == 2) {
		strcpy(id, lexList[lexemeListIndex].name);
	}
	//Takes care of numbers, always represented by "3 | number"
	else if (token == 3) {
		num = lexList[lexemeListIndex].numberValue;
	}

	lexemeListIndex++;
	return token;
}

void vardeclaration(FILE* ofp) {
	if (token == 28)
	{
		strcat(codeline[index], "const int ");
	}
	else
	{
		strcat(codeline[index], "int ");
	}
	vari = 1;
	epression(ofp);
	vari = 0;
}

void procedureprocess(FILE* ofp)
{
	token = getNextToken();
	strcat(codeline[0], "void ");
	strcat(codeline[0], id);
	strcat(codeline[0], "();\n");
	lev++;
	index++;
	semi++;
	strcat(codeline[index], "void ");
	strcat(codeline[index], id);
	strcat(codeline[index], "()\n{\n");
}

void beginprocess(FILE* ofp)
{
	if (lev == 0)
	{
		index = 9;
		strcat(codeline[index], "void main()\n{\n");
	}
}

void writeprocess(FILE* ofp)
{
	//printf(ofp, "printf(\"%%d\", ");
	strcat(codeline[index], "printf(\"%d\\n\", ");
	while (token != 18)
	{
		symprocess(ofp);
		token = getNextToken();
	}
	//fprintf(ofp, ");\n");
	strcat(codeline[index], ");\n");
}

void readprocess(FILE* ofp)
{
	//fprintf(ofp, "scanf(\"%%d\", ");
	strcat(codeline[index], "scanf(\"%d\", &");
	while (token != 18)
	{
		symprocess(ofp);
		token = getNextToken();
	}
	//fprintf(ofp, ");\n");
	strcat(codeline[index], ");\n");
}

void symprocess(FILE* ofp)
{
	//token = getNextToken();
	switch (token)
	{
	case 2:
		//fprintf(ofp, "%s", id);
		strcat(codeline[index], id);
		break;
	case 3:
		//fprintf(ofp, "%d", num);
		itoa(num, id, 10);
		strcat(codeline[index], id);
		break;
	case 4:
		//fprintf(ofp, " + ");
		strcat(codeline[index], " + ");
		break;
	case 5:
		//fprintf(ofp, " + ";
		strcat(codeline[index], " - ");
		break;
	case 6:
		//fprintf(ofp, " * ");
		strcat(codeline[index], " * ");
		break;
	case 7:
		//fprintf(ofp, " / ");
		strcat(codeline[index], " / ");
		break;
	case 8:
		//fprintf(ofp, " / ");
		token = getNextToken();
		strcat(codeline[index], id);
		strcat(codeline[index], "% 2 == 1");
		break;
	case 9:
		if (vari == 1) {
			strcat(codeline[index], " = ");
		}
		else {
			strcat(codeline[index], " == ");
		}
		//fprintf(ofp, " == ");
	
		break;
	case 10:
		//fprintf(ofp, " <> ");
		strcat(codeline[index], " <> ");
		break;
	case 11:
		//fprintf(ofp, " < ");
		strcat(codeline[index], " < ");
		break;
	case 12:
		//fprintf(ofp, " <= ");
		strcat(codeline[index], " <= ");
		break;
	case 13:
		//fprintf(ofp, " > ");
		strcat(codeline[index], " > ");
		break;
	case 14:
		//fprintf(ofp, " >= ");
		strcat(codeline[index], " >= ");
		break;
	case 17:
		//fprintf(ofp, ", ");
		strcat(codeline[index], ", ");
		break;
	case 20:
		//fprintf(ofp, " = ");
		strcat(codeline[index], " = ");
		break;
	case 27:
		//fprintf(ofp, " = ");
		callprocess(ofp);
		break;
	default:
		break;
	}
}

void ifprocess(FILE* ofp)
{
	//fprintf(ofp, "if (");
	strcat(codeline[index], "if (");
	while (token != 24)
	{
		symprocess(ofp);
		token = getNextToken();
	}
	//fprintf(ofp, ")\n{\n");
	strcat(codeline[index], ")\n{\n");
	while (token != 33 && token != 18)
	{
		symprocess(ofp);
		token = getNextToken();
	}
	//fprintf(ofp, ";\n}\n");
	strcat(codeline[index], ";\n}\n");
	if (token == 33) 
	{
		//fprintf(ofp, "else\n{\n");
		strcat(codeline[index], "else\n{\n");
		while (token != 18)
		{
			symprocess(ofp);
			token = getNextToken();
		}
		//fprintf(ofp, ";\n}\n");
		strcat(codeline[index], ";\n}\n");
	}
}

void whileprocess(FILE* ofp)
{
	//fprintf(ofp, "while (");
	lev++;
	whilei = 1;
	strcat(codeline[index], "while (");
	while (token != 26)
	{
		symprocess(ofp);
		token = getNextToken();
	}
	//fprintf(ofp, ")\n{\n");
	strcat(codeline[index], ")\n{\n");
}

void callprocess(FILE* ofp) {
	token = getNextToken();
	//fprintf(ofp, "%s()", id);
	strcat(codeline[index], id);
	strcat(codeline[index], "();\n");
	token = getNextToken();
}

void epression(FILE* ofp)
{
	token = getNextToken();
	while (token != 18 && token != 19)
	{
		switch (token)
		{
		case 21:
			beginprocess(ofp);
			break;
		case 22:
			
			strcat(codeline[index], "}\n");
			if (whilei == 0) {
				lev--;
				index--;
				token = getNextToken();
			}
			else {
				lev--;
				whilei = 0;
				token = getNextToken();
			}
			//fprintf(ofp, "}\n");		
			break;
		case 23:
			ifprocess(ofp);
			break;
		case 25:
		
			whileprocess(ofp);
			break;
		case 27:
			callprocess(ofp);
			break;
		case 28:
			vardeclaration(ofp);
			break;
		case 29:
			vardeclaration(ofp);
			break;
		case 30:
			procedureprocess(ofp);
			break;
		case 31:
			writeprocess(ofp);
			break;
		case 32:
			readprocess(ofp);
			break;
		default:
			symprocess(ofp);
			break;
		}
		if (token != 19)
		{
			token = getNextToken();
		}
	}
	if (semi == 0 && token != 19) 
	{
		//fprintf(ofp, ";\n");
		strcat(codeline[index], ";\n");
	}
	else {
		semi--;
	}
}