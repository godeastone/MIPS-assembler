#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*******************************************************
 * Function Declaration
 *
 *******************************************************/
char *change_file_ext(char *str);

typedef struct label
{
	char name[100];
	long long int address;
}label;

label label_list[100];
int label_index = 0;

void R_type(int op, int rs, int rt, int rd, int shamt, int funct);
void I_type(int op, int rs, int rt, long long int address);
void I_type_2(int op, int rs, int rt, long long int address);
void J_type(int op, long long int address);
void J_type_2(int op, long long int address);

long long int bincode[1000];
int bincode_index = 0;

long long int data[1000];
int data_index = 0;

int regist(char *reg);
int signExtimm(char *imm);
long long int int_label(char *label);


/*******************************************************
 * Function: main
 *
 * Parameters:
 *  int
 *      argc: the number of argument
 *  char*
 *      argv[]: array of a sting argument
 *
 * Return:
 *  return success exit value
 *
 * Info:
 *  The typical main function in C language.
 *  It reads system arguments from terminal (or commands)
 *  and parse an assembly file(*.s).
 *  Then, it converts a certain instruction into
 *  object code which is basically binary code.
 *
 *******************************************************/
int main(int argc, char *argv[])
{
	FILE *input, *output;
	char *filename;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <*.s>\n", argv[0]);
		fprintf(stderr, "Example: %s sample_input/example?.s\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	input = fopen(argv[1], "r");
	if (input == NULL) {
		perror("ERROR");
		exit(EXIT_FAILURE);
	}

	filename = strdup(argv[1]); // strdup() is not a standard C library but fairy used a lot.

	if (change_file_ext(filename) == NULL) {
		fprintf(stderr, "'%s' file is not an assembly file.\n", filename);
		exit(EXIT_FAILURE);
	}

	output = fopen(filename, "w");

	if (output == NULL) {
		perror("ERROR");
		exit(EXIT_FAILURE);

	}
	/////////////////////////////////////////////////////////////////////////
	int datasize_count = 0;
	int instruction_count = 0;
	int count = 0;
	int dataSectionSize = 0;
	int datacount = 0;

	while (!feof(input))
	{

		char *ptr;
		char strTemp1[500];

		while (ptr = fgets(strTemp1, sizeof(strTemp1), input))
		{
			if (strstr(ptr, ".data"))
			{
				break;
			}
		}
		while (ptr = fgets(strTemp1, sizeof(strTemp1), input))
		{
			if (strstr(ptr, ".word"))
			{
				char *first;
				char *second;
				char *third;
				label newLabel;
				char temp[100];
				strcpy(temp, ptr);




				///
				if (strstr(temp, ":") != NULL)
				{
					strcpy(newLabel.name, strtok(ptr, ":"));
					newLabel.address = 0x10000000 + (datasize_count) * 4;
					datasize_count++;
					label_list[label_index] = newLabel;
					label_index++;
					datacount++;

					first = strtok(temp, ":");
					second = strtok(NULL, " \t");
					third = strtok(NULL, " \t");
					data[data_index++] = signExtimm(third);
				}
				else
				{
					strcpy(newLabel.name, "he");
					newLabel.address = 0x10000000 + (datasize_count) * 4;
					datasize_count++;
					label_list[label_index] = newLabel;
					label_index++;

					datacount++;
					first = strtok(temp, " \t");
					second = strtok(NULL, " \t");
					data[data_index++] = signExtimm(second);
				}
				///

			}
			if (strstr(ptr, ".text"))
			{
				break;
			}
		}

		while (ptr = fgets(strTemp1, sizeof(strTemp1), input))
		{

			if (strstr(ptr, ":"))
			{
				label newLabel;
				char temp[100];
				strcpy(temp, ptr);
				strcpy(newLabel.name, strtok(temp, ":"));
				newLabel.address = 0x400000 + (count * 4) + 4;
				label_list[label_index] = newLabel;
				label_index++;

			}
			else
			{
				char *ju;
				ju = strtok(ptr, " ,\t");


				if (strcmp(ju, "addiu") == 0)
				{
					count++;
				}
				if (strcmp(ju, "addu") == 0)
				{
					count++;
				}
				if (strcmp(ju, "and") == 0)
				{
					count++;
				}
				if (strcmp(ju, "andi") == 0)
				{
					count++;
				}
				if (strcmp(ju, "beq") == 0)
				{
					count++;
				}
				if (strcmp(ju, "bne") == 0)
				{
					count++;
				}
				if (strcmp(ju, "j") == 0)
				{
					count++;
				}
				if (strcmp(ju, "jal") == 0)
				{
					count++;
				}
				if (strcmp(ju, "jr") == 0)
				{
					count++;
				}
				if (strcmp(ju, "lui") == 0)
				{
					count++;
				}
				if (strcmp(ju, "lw") == 0)
				{
					count++;
				}
				if (strcmp(ju, "la") == 0)
				{
					char *first;
					char *second;

					first = strtok(NULL, " ,\t");
					second = strtok(NULL, " ,\t");

					int ab = 0;
					while (1)
					{
						if (second[ab] == '\n')
						{
							second[ab] = '\0';
							break;
						}
						else
						{
							ab++;
						}
					}

					long long int laaddress = int_label(second);

					if ((laaddress & 65535) == 0)
					{
						count++;

					}
					else
					{
						count += 2;

					}
				}
				if (strcmp(ju, "nor") == 0)
				{
					count++;
				}
				if (strcmp(ju, "or") == 0)
				{
					count++;
				}
				if (strcmp(ju, "ori") == 0)
				{
					count++;
				}
				if (strcmp(ju, "sltiu") == 0)
				{
					count++;
				}
				if (strcmp(ju, "sltu") == 0)
				{
					count++;
				}
				if (strcmp(ju, "sll") == 0)
				{
					count++;
				}
				if (strcmp(ju, "srl") == 0)
				{
					count++;
				}
				if (strcmp(ju, "sw") == 0)
				{
					count++;
				}
				if (strcmp(ju, "subu") == 0)
				{
					count++;
				}

			}
		}
	}


	////////////////////////////////////////크기계산 과정

	fseek(input, 0, SEEK_SET);

	while (!feof(input))
	{
		char *ptr1;

		char strTemp3[500];

		while (ptr1 = fgets(strTemp3, sizeof(strTemp3), input))
		{
			if (strstr(ptr1, ".text"))
			{

				break;
			}
		}


		while (ptr1 = fgets(strTemp3, sizeof(strTemp3), input))
		{
			if (ptr1 == NULL)
			{
				continue;
			}

			if (strstr(ptr1, ":"))
			{
				continue;
			}

			else
			{
				char assemblyCodeline[50];
				strcpy(assemblyCodeline, ptr1);


				char *opcode = NULL;
				char *rd_rt = NULL;
				char *rs_rt = NULL;
				char *rt_imme = NULL;

				opcode = strtok(assemblyCodeline, " ,\n\t\r");
				if (opcode == NULL)
				{
					break;
				}
				else if (opcode != NULL)
				{
					rd_rt = strtok(NULL, " ,\n\t\r");
				}
				if (rd_rt != NULL)
				{
					rs_rt = strtok(NULL, " ,\n\t\r");
				}
				if (rs_rt != NULL)
				{
					rt_imme = strtok(NULL, " ,\n\t\r");
				}


				if (strcmp(opcode, "addiu") == 0)
				{
					I_type(9, regist(rs_rt), regist(rd_rt), signExtimm(rt_imme));

				}
				else if (strcmp(opcode, "addu") == 0)
				{
					R_type(0, regist(rs_rt), regist(rt_imme), regist(rd_rt), 0, 33);

				}
				else if (strcmp(opcode, "and") == 0)
				{
					R_type(0, regist(rs_rt), regist(rt_imme), regist(rd_rt), 0, 36);

				}
				else if (strcmp(opcode, "andi") == 0)
				{
					I_type(12, regist(rs_rt), regist(rd_rt), signExtimm(rt_imme));

				}
				else if (strcmp(opcode, "beq") == 0)
				{


					long long int address = int_label(rt_imme) - (bincode_index * 4);
					I_type_2(4, regist(rd_rt), regist(rs_rt), (address / 4));



				}
				else if (strcmp(opcode, "bne") == 0)
				{

					long long int address = int_label(rt_imme) - (bincode_index * 4);
					I_type_2(5, regist(rd_rt), regist(rs_rt), (address / 4));

				}
				else if (strcmp(opcode, "j") == 0)
				{
					J_type_2(2, (int_label(rd_rt) >> 2));

				}
				else if (strcmp(opcode, "jal") == 0)
				{
					J_type_2(3, (int_label(rd_rt) >> 2));

				}
				else if (strcmp(opcode, "jr") == 0)
				{
					R_type(0, regist(rd_rt), 0, 0, 0, 8);

				}
				else if (strcmp(opcode, "lui") == 0)
				{
					I_type(15, 0, regist(rd_rt), signExtimm(rs_rt));

				}
				else if (strcmp(opcode, "lw") == 0)
				{
					char *offset = strtok(rs_rt, "()");
					char *rs = strtok(NULL, "()");
					I_type(35, regist(rs), regist(rd_rt), signExtimm(offset));

				}
				else if (strcmp(opcode, "nor") == 0)
				{
					R_type(0, regist(rs_rt), regist(rt_imme), regist(rd_rt), 0, 39);

				}
				else if (strcmp(opcode, "or") == 0)
				{
					R_type(0, regist(rs_rt), regist(rt_imme), regist(rd_rt), 0, 37);

				}
				else if (strcmp(opcode, "ori") == 0)
				{
					I_type(13, regist(rs_rt), regist(rd_rt), signExtimm(rt_imme));

				}
				else if (strcmp(opcode, "sltiu") == 0)
				{
					I_type(11, regist(rs_rt), regist(rd_rt), signExtimm(rt_imme));

				}
				else if (strcmp(opcode, "sltu") == 0)
				{
					R_type(0, regist(rs_rt), regist(rt_imme), regist(rd_rt), 0, 43);

				}
				else if (strcmp(opcode, "sll") == 0)
				{
					R_type(0, 0, regist(rs_rt), regist(rd_rt), signExtimm(rt_imme), 0);

				}
				else if (strcmp(opcode, "srl") == 0)
				{
					R_type(0, 0, regist(rs_rt), regist(rd_rt), signExtimm(rt_imme), 2);

				}
				else if (strcmp(opcode, "sw") == 0)
				{
					char *offset = strtok(rs_rt, "()");
					char *rs = strtok(NULL, "()");
					I_type(43, regist(rs), regist(rd_rt), signExtimm(offset));

				}
				else if (strcmp(opcode, "subu") == 0)
				{
					R_type(0, regist(rs_rt), regist(rt_imme), regist(rd_rt), 0, 35);

				}
				else if (strcmp(opcode, "la") == 0)
				{
					long long int address = int_label(rs_rt);
					if ((address & 65535) == 0)
					{
						I_type(15, 0, regist(rd_rt), (address >> 16));

					}
					else
					{
						I_type(15, 0, regist(rd_rt), (address >> 16));
						I_type(13, regist(rd_rt), regist(rd_rt), (address & 65535));

					}
				}
			}
		}
	}





	/////////////////////////////////////////명령어 계산과정

	int a, b, c, d, e, f, g, h, k;

	int ic = (count * 4);
	int dc = (datacount * 4);
	{
		int i, j, decimal;
		decimal = ic;
		unsigned int mask = 1 << 31;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 4; j++) {

				char c = (decimal & mask) == 0 ? '0' : '1';

				fprintf(output, "%c", c);

				mask >>= 1;
			}


		}
	}
	{
		int i, j, decimal;
		decimal = dc;
		unsigned int mask = 1 << 31;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 4; j++) {

				char c = (decimal & mask) == 0 ? '0' : '1';

				fprintf(output, "%c", c);

				mask >>= 1;
			}


		}
	}




	for (f = 0; f < bincode_index; f++)
	{
		int i, j, decimal;
		decimal = bincode[f];
		unsigned int mask = 1 << 31;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 4; j++) {

				char c = (decimal & mask) == 0 ? '0' : '1';

				fprintf(output, "%c", c);

				mask >>= 1;
			}


		}


	}


	/////////////////////////////////////////명령어 출력과정

	for (f = 0; f < datacount; f++)
	{
		int i, j, decimal;
		decimal = data[f];
		unsigned int mask = 1 << 31;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 4; j++) {

				char c = (decimal & mask) == 0 ? '0' : '1';

				fprintf(output, "%c", c);

				mask >>= 1;
			}


		}


	}

	/////////////////////////////////////////데이터 출력
	fclose(input);
	fclose(output);
	exit(EXIT_SUCCESS);
}


/*******************************************************
 * Function: change_file_ext
 *
 * Parameters:
 *  char
 *      *str: a raw filename (without path)
 *
 * Return:
 *  return NULL if a file is not an assembly file.
 *  return empty string
 *
 * Info:
 *  This function reads filename and converst it into
 *  object extention name, *.o
 *
 *******************************************************/

char
*change_file_ext(char *str)
{
	char *dot = strrchr(str, '.');

	if (!dot || dot == str || (strcmp(dot, ".s") != 0)) {
		return NULL;
	}

	str[strlen(str) - 1] = 'o';
	char b[4] = "abc";
	//char * a = b;
	return "";
}


void R_type(int op, int rs, int rt, int rd, int shamt, int funct)
{
	long long int result = 0;
	result = (op << 26);
	result |= (rs << 21);
	result |= (rt << 16);
	result |= (rd << 11);
	result |= (shamt << 6);
	result |= funct;
	bincode[bincode_index] = result;
	bincode_index++;
}

void I_type(int op, int rs, int rt, long long int address)
{
	long long int result = 0;
	result = (op << 26);
	result |= (rs << 21);
	result |= (rt << 16);
	result |= (address & 65535);
	bincode[bincode_index] = result;
	bincode_index++;
}

void I_type_2(int op, int rs, int rt, long long int address)
{
	long long int result = 0;
	result = (op << 26);
	result |= (rs << 21);
	result |= (rt << 16);
	result |= (address & 65535);
	bincode[bincode_index] = result - 2;
	bincode_index++;
}

void J_type(int op, long long int address)
{
	long long int result = 0;
	result = (op << 26);
	result |= address;
	bincode[bincode_index] = result;
	bincode_index++;
}

void J_type_2(int op, long long int address)
{
	long long int result = 0;
	result = (op << 26);
	result |= address;
	bincode[bincode_index] = result - 1;
	bincode_index++;
}

int regist(char *reg)
{
	char *p = strtok(reg, "$");
	int result = atoi(p);

	return result;
}

int signExtimm(char *imm)
{
	if (strstr(imm, "0x") != NULL)
	{
		return (int)strtol(imm, NULL, 0);
	}
	else
	{
		return atoi(imm);
	}
}

long long int int_label(char *label)
{
	int a;
	for (a = 0; a < label_index; a++)
	{
		if (strcmp(label_list[a].name, label) == 0)
		{
			return label_list[a].address;
		}
	}
}

