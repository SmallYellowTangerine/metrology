#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <clocale>



//функция для копирования содержимого файла в строку
char *filetostring(char *filename)
{
    FILE *file=fopen(filename, "r");

    if (file==NULL)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long int filesize=ftell(file);
    rewind(file);
    char *content=(char *)calloc(filesize+1, 1);
    fread(content, 1, filesize, file);

	fclose(file);

    return content;
}



void main()
{
	setlocale(LC_ALL, "Russian");

	//создание/открытие файла, в который будет записываться код без комментариев
	FILE *fopen(
		const char *filename,
		const char *mode
		);
	FILE *resultcode;
	resultcode=fopen("resultcode.txt", "w+");

	//копирование исходного кода из файла в строку
	char *sourcestr;
	sourcestr=filetostring("cpp.txt");

	//удаление комментариев
	int state=0; //   0-код, 1-внутри//комментария, 2-внутри/*комментария
	char *resultstr;
	int j=0;

	while (j<strlen(sourcestr))
	{
		switch (state) 
		{
		//   /=47
		case 0:
			if (sourcestr[j]==47)
			{
				if (sourcestr[j+1]==47)
				{
					state=1;
					j=j+2;
				}
				if (sourcestr[j+1]==42)
				{
					state=2;
					j=j+2;
				}
			}
			else
			{
				fputc(sourcestr[j], resultcode);
				j++;
			}
			break;
		// new string=10
		case 1:
			if (sourcestr[j]==10)
			{
					state=0;
					fputc(sourcestr[j], resultcode);
					fputc(sourcestr[j+1], resultcode);
					j=j+2;
			}
			else
				j++;
			break;
		//   /=47, *=42
		case 2:
			if (sourcestr[j]==42)
			{
				if (sourcestr[j+1]==47)
				{
					state=0;
					j=j+2;
				}
			}
			else
				j++;
			break;
		} //end of switch
	} //end of while
	
	int fclose(
		FILE *resultcode
		);

	resultstr=filetostring("resultcode.txt");

	printf("Комментарии в коде были удалены\n");
		


	//подсчет операторов
	int i=0;
	int CL_abs=0; //абсолютная сложность программы
	int alloperators=0; 

	while (i<strlen(resultstr))
	{
		//пропуск всего в кавычках
		if (resultstr[i]==34) // ""
		{
			do 
			{	i++;	}
			while (resultstr[i]!=34);
		}
		//подсчет всех операторов
		if ( (((resultstr[i]==60) && (resultstr[i+1]==60)) && (resultstr[i+2]==61)) // <<=
			|| (((resultstr[i]==62) && (resultstr[i+1]==62)) && (resultstr[i+2]==61)) // >>=
			|| (((resultstr[i]==45) && (resultstr[i+1]==62)) && (resultstr[i+2]==42)) // ->*
			|| ((resultstr[i]==110) && (resultstr[i+1]==101) && (resultstr[i+2]==119)) // new
			)
		{
			alloperators++;
			i=i+3;
			continue;
		}
		if ( ((resultstr[i]==61) && (resultstr[i+1]==61)) // ==
			|| ((resultstr[i]==43) && (resultstr[i+1]==43)) // ++ 
			|| ((resultstr[i]==45) && (resultstr[i+1]==45)) // --
			|| ((resultstr[i]==33) && (resultstr[i+1]==33)) // !!
			|| ((resultstr[i]==33) && (resultstr[i+1]==61)) // !=
			|| ((resultstr[i]==60) && (resultstr[i+1]==60)) // <<
			|| ((resultstr[i]==60) && (resultstr[i+1]==61)) // <=
			|| ((resultstr[i]==62) && (resultstr[i+1]==62)) // >>
			|| ((resultstr[i]==62) && (resultstr[i+1]==61)) // >=
			|| ((resultstr[i]==38) && (resultstr[i+1]==38)) // &&
			|| ((resultstr[i]==124) && (resultstr[i+1]==124)) // ||
			|| ((resultstr[i]==43) && (resultstr[i+1]==61)) // +=
			|| ((resultstr[i]==45) && (resultstr[i+1]==61)) // -=
			|| ((resultstr[i]==42) && (resultstr[i+1]==61)) // *=
			|| ((resultstr[i]==47) && (resultstr[i+1]==61)) // /=
			|| ((resultstr[i]==37) && (resultstr[i+1]==61)) // %=
			|| ((resultstr[i]==38) && (resultstr[i+1]==61)) // &=
			|| ((resultstr[i]==124) && (resultstr[i+1]==61)) // |=
			|| ((resultstr[i]==94) && (resultstr[i+1]==61)) // ^=
			|| ((resultstr[i]==45) && (resultstr[i+1]==62)) // ->
			|| ((resultstr[i]==46) && (resultstr[i+1]==42)) // .*
			|| ((resultstr[i]==58) && (resultstr[i+1]==58)) // ::
			|| ((resultstr[i]==63) && (resultstr[i+1]==46)) // ?.
			|| ((resultstr[i]==63) && (resultstr[i+1]==63)) // ??
			|| ((resultstr[i]==105) && (resultstr[i+1]==115)) // is
			|| ((resultstr[i]==97) && (resultstr[i+1]==115)) // as
			)
		{
			alloperators++;
			i=i+2;
			continue;
		}
		if ((resultstr[i]==42) // *
			|| (resultstr[i]==47) // /
			|| (resultstr[i]==37) // %
			|| (resultstr[i]==126) // ~ 
			|| (resultstr[i]==94) // ^
			|| (resultstr[i]==61) // =
			|| (resultstr[i]==43) // +
			|| (resultstr[i]==45) // -
			|| (resultstr[i]==33) // !
			|| (resultstr[i]==60) // <
			|| (resultstr[i]==62) // >
			|| (resultstr[i]==38) // &
			|| (resultstr[i]==124) // |
			|| (resultstr[i]==91) // [
			|| (resultstr[i]==46) // .
			|| (resultstr[i]==44) // ,
			|| (resultstr[i]==40) // ( 			
			)
		{
			alloperators++;
			i++;
			continue;
		}
		if ( ( (resultstr[i]==116) && (resultstr[i+1]==104) && (resultstr[i+2]==114) 
				&& (resultstr[i+3]==111) && (resultstr[i+4]==119) ) //throw
			)
		{
			alloperators++;
			i=i+5;
			continue;
		}
		if (((resultstr[i]==100) && (resultstr[i+1]==101) && (resultstr[i+2]==108) 
				&& (resultstr[i+3]==101) && (resultstr[i+4]==116) && (resultstr[i+4]==101)) //delete
			|| ( (resultstr[i]==116) && (resultstr[i+1]==121) && (resultstr[i+2]==112) 
				&& (resultstr[i+3]==101) && (resultstr[i+4]==111) && (resultstr[i+4]==102) ) //typeof
			|| ( (resultstr[i]==115) && (resultstr[i+1]==105) && (resultstr[i+2]==122) 
				&& (resultstr[i+3]==101) && (resultstr[i+4]==111) && (resultstr[i+4]==102) ) //sizeof
			)
		{
			alloperators++;
			i=i+6;
			continue;
		}
		if ( ( (resultstr[i]==99) && (resultstr[i+1]==104) && (resultstr[i+2]==101) 
				&& (resultstr[i+3]==99) && (resultstr[i+4]==107) && (resultstr[i+4]==101) 
				&& (resultstr[i+3]==100) ) //checked
			)
		{
			alloperators++;
			i=i+7;
			continue;
		}
		if ( ( (resultstr[i]==100) && (resultstr[i+1]==101) && (resultstr[i]==108) 
				&& (resultstr[i+1]==101) && (resultstr[i+2]==103) && (resultstr[i+3]==97) 
				&& (resultstr[i+4]==116) && (resultstr[i+4]==101) ) //delegate
			)
		{
			alloperators++;
			i=i+8;
			continue;
		}
		if ( ( (resultstr[i]==117) && (resultstr[i+1]==110) && (resultstr[i]==99) 
				&& (resultstr[i+1]==104) && (resultstr[i+2]==101) && (resultstr[i+3]==99) 
				&& (resultstr[i+4]==107) && (resultstr[i+4]==101) && (resultstr[i+3]==100) ) //unchecked
			)
		{
			alloperators++;
			i=i+9;
			continue;
		}
		//подсчет if и ?:
		if (((resultstr[i]==105) && (resultstr[i+1]==102)) //if
			|| ( (resultstr[i]==63) && (resultstr[i+1]!=63) && (resultstr[i+1]!=46) 
				 && (resultstr[i+1]!=91) ) //?:
			)
		{
			alloperators++;
			CL_abs++;
			i=i+2;
			continue;
		}

		i++;

	}

	float cl_rel=0; //относительная сложность программы
	cl_rel=(float)CL_abs/(float)alloperators;

	//printf("Все операторы=%d \n", alloperators);
	printf("Абсолютная сложность программы CL=%d \n", CL_abs);
	printf("Относительная сложность программы cl=%f \n", cl_rel);



	//подсчет уровня вложенности if'ов
	int CLI=0; //максимальный уровень вложенности
	int emptyedges=0; //фигурные скобки, не относящиеся к if
	int edges=0; //фигурные скобки, относящиеся к if
	int temp=0;
	i=0;

	while (i<strlen(resultstr))
	{
		//если встретились фигурные скобки
		if (resultstr[i]==123) // {
		{
			emptyedges++;
		}
		if (resultstr[i]==125) // }
		{
			if ( (emptyedges==0) && (edges!=0) )
			{
				edges--;
				temp--;
			}
			else
				emptyedges--;
		}
		//если встретились if или else
		if (((resultstr[i]==105) && (resultstr[i+1]==102)) //if
			|| ( (resultstr[i]==101) && (resultstr[i+1]==108) && (resultstr[i]==115) && (resultstr[i+1]==101) ) //else
			)
		{
			if (edges>0)
				temp++;
			while ( (resultstr[i]!=123) && (resultstr[i]!=59) ) // { или ;
				i++;
			if (resultstr[i]==123)
				edges++;
			if (resultstr[i]==59)
			{
				if (temp>CLI)
					CLI=temp;
			}
		}
		//если встретились ?:
		if (( (resultstr[i]==63) && (resultstr[i+1]!=63) && (resultstr[i+1]!=46) 
				 && (resultstr[i+1]!=91) ) //?:
			)
		{
			if (edges>0)
			{
				temp++;
				if (temp>CLI)
					CLI=temp;
			}
		}
		i++;
	}

	printf("Максимальный уровень вложенности CLI=%d \n", CLI/2); 



	//завершение
	free(sourcestr);
	free(resultstr);

	_flushall();
	getchar();
}
