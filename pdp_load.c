# include <stdio.h>
#include <string.h>
# include <assert.h>

typedef unsigned char byte;
typedef unsigned short int word;
typedef word adr;

word mem [64 * 1024];

# define LO(x) ((x) & 0xFF)
# define HI(x) (((x)>> 8) & 0xFF)

byte b_read (adr a); // читает из "старой памяти" mem байт с "адресом" a.
void b_write (adr a, byte val); // пишет значение val в "старую память" mem в байт с "адресом" a.
word w_read (adr a); // читает из "старой памяти" mem слово с "адресом" a.
void w_write (adr a, word val); // пишет значение val в "старую память" mem в слово с "адресом" a.
void load_file( );

byte b_read(adr a)
{
byte res;
if((a % 2) == 0)
res = (LO(mem[a]));
else if((a % 2) != 0)
res = (HI(mem[a - 1]));
a -= 1;
return res; 
}

word w_read(adr a)
{
return mem[a];
}

void w_write(adr a, word val)
{
mem[a] = val;
}

void b_write(adr a, byte val)
{
word b =0;
if((a % 2) == 0)
mem[a] |= val;
else if((a % 2) != 0)
b = val;
b <<= 8;
mem[a - 1] = mem[a-1] | b;
}

void mem_dump(adr start, word n);

void load_file( )
{
unsigned int a;
unsigned int b;
unsigned int val;
int i = 0;
FILE *f = stdin;
while (fscanf(f, "%x%x", &a, &b) == 2)
{
for (i = a; i < (a + b); i++)
{
fscanf(f,"%x", & val);
b_write (i,val);
}
}
}

void mem_dump(adr start, word n)
{
assert (start % 2 == 0);
int i = 0;
for(i = 0; i < n; i = i + 2)
{
printf("%06o : %06o\n", (start + i), mem[start + i]);
}
}
