import java.io.*;
class cdma1
{
BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
int dataa,datab;
int keya[]=new int [6];
int keyb[]=new int [6];
int key1[]=new int [6];
int key2[]=new int [6];
int key3[]=new int[6];
int ina ,inb;

public void getdata()throws IOException
{
System.out.println("A-Enter data bit");
ina=Integer.parseInt(br.readLine());
if(ina>1 ||ina<0)
System.out.println("Error enter binary");

System.out.println("B-Enter data bit");
inb=Integer.parseInt(br.readLine());
if(inb>1 ||inb<0)
System.out.println("Error enter binary");

System.out.println("A-Enter the 6bit binary key");
for(int i=0;i<6;i++)
{keya[i]=Integer.parseInt(br.readLine());
if(keya[i]>1 ||keya[i]<0)
{System.out.println("Error enter binary");
}
}
System.out.println("B-Enter the 6 bit binary key");
for(int i=0;i<6;i++)
{keyb[i]=Integer.parseInt(br.readLine());
if(keyb[i]>1 ||keyb[i]<0)
{System.out.println("Error enter binary");
}
}
}

public void compute()throws IOException
{

if (ina==0)
dataa=-1;
else
dataa=1;
if(inb==0)
datab=-1;
else
datab=1;

for(int i=0;i<6;i++)
{
if(keya[i]==0)
{
key1[i]=-1;
}
else
{
key1[i]=1;
}
}

for(int i=0;i<6;i++)
{
if(keyb[i]==0)
{
key2[i]=-1;
}
else
{
key2[i]=1;
}
}

for(int i=0;i<6;i++)
{
keya[i]=key1[i]*dataa;
keyb[i]=key2[i]*datab;
key3[i]=keya[i]+keyb[i];
}

for(int i=0;i<6;i++)
{
keya[i]=key3[i]*key1[i];
keyb[i]=key3[i]*key2[i];
}
int totala=0;
int totalb=0;
for(int i=0;i<6;i++)
{
totala=totala+keya[i];
totalb=totalb+keyb[i];
}

System.out.println("Transformed key a");
for(int i=0;i<6;i++)
System.out.print(key1[i]+"  ");

System.out.println("Transformed key b");
for(int i=0;i<6;i++)
System.out.print(key2[i]+"  ");

System.out.println("The sum of a is "+totala);
System.out.println("The sum of b is "+totalb);
if(totala>=0)
System.out.println("The data entered by A is 1");
else
System.out.println("The data entered by A is 0");

if(totalb>=0)
System.out.println("The data entered by B is 1");
else
System.out.println("The data entered by B is 0");

}

}
class cdma
{
public static void main(String args[])throws IOException
{
cdma1 c=new cdma1();
c.getdata();
c.compute();
}
}

/*
output:

C:\jdk1.3\bin>javac cdma.java

C:\jdk1.3\bin>java cdma
A-Enter data bit
1
B-Enter data bit
0
A-Enter the 6bit binary key
0
1
0
0
1
1
B-Enter the 6 bit binary key
1
1
0
1
0
1
Transformed key a
-1  1  -1  -1  1  1
Transformed key b
1  1  -1  1  -1  1
The sum of a is 6
The sum of b is -6
The data entered by A is 1
The data entered by B is 0

C:\jdk1.3\bin>
*/
