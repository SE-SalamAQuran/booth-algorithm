/**********************************************************************
 tested in turbo c++ && dosbox  will!  work in dev

 program to inolement booth algorithm!!!
 arrays represent respective registers--br stores multiplicand qr stores multiplier

 author: @mayankf599@gmail.com
 **********************************************************************/

 #include<stdio.h>
 #include<conio.h>
 #include<string.h>
 void bingen(int,int[]);       //binary no generator
 int complement(int[],int[]);  //function to find 2's complement
 int retcarry(int,int);
 int retsum(int,int);          //returns resulting sum
 int rsum(int,int,int);        //for two nos
 int rcarry(int,int,int);      //full adder carry logic
 void add(int[],int[]);        //function to add 2 binary no's
 void substract(int[],int[]);  //function to sub 2 binary no's
 void ashr(int[],int[]);       /*right shift function*/
 int test(int ,int);
 int comp(int);                /*function for binary no complement*/
 void evaluate(int[],int []);  //function to convert binary no to decimal no representation
 int pow(int);                 //function to raise 2 to it's powers

 int main()
{     int i,num1,num2,comp[5],br[5]={0,0,0,0,0},ac[5]={0,0,0,0,0},qr[5]={0,0,0,0,0},txt,qn1=0,qn;
      int res,sign1,sign2;
      char *str,*str1;
      printf("\n enter number 1:");
      scanf("%s",str);

      printf("\n enter number 2:");
      scanf("%s",str1);

      if(*str=='-')
      {
	 str+=1;
	 num1=atoi(str);
	 bingen(num1,br);
	 complement(br,br);
      }
      else
      {  num1=atoi(str);
	 bingen(num1,br);
      }

      if(*str1=='-')
      {
	 str1+=1;
	 num2=atoi(str1);
	 bingen(num2,qr);
	 complement(qr,qr);
      }
      else
      {  num2=atoi(str1);
	 bingen(num2,qr);
      }

      printf("\n br:");

      for(i=0;i<5;i++)
      printf("%d",br[i]);
	  printf("\n qr:");

      for(i=0;i<5;i++)
      printf("%d",qr[i]);
      printf("\n2's complement of br:");

      complement(br,comp);


      for(i=0;i<5;i++)
      printf("%d",comp[i]);


       for(i=0;i<5;i++)
      {
	qn=qr[4];
	res=test(qn,qn1);

	if(res==1)
	{
	 substract(ac,comp);      //comp holds br's complement
	 ashr(ac,qr);
	 qn1=qn;
	}

	if(res==2)
	{
	 add(ac,br);
	 ashr(ac,qr);
	 qn1=qn;
	}

	if(res==3)
	{
	 ashr(ac,qr);
	 qn1=qn;
	}
      }
      printf("\nresult:");
       for(i=0;i<5;i++)
       printf("%d",ac[i]);

       for(i=0;i<5;i++)
       printf("%d",qr[i]);

       evaluate(ac,qr);
	printf("\n");
	getch();
}


  void bingen(int x,int arr[5])                   //binary no generator
 { int qt,i=4;           //qt=quotient    i=index
   int rem;
   while(1)
  {  rem=x%2;
     arr[i--]=rem;
     x=x/2;
     if(x==0||x==1)
     break;
  }
  arr[i--]=x;
 }




   int test(int x,int y)
  {
    if(x==1&&y==0)       //if q[n]=1 and q[n+1]=0
    return 1;

    if(x==0&&y==1)      //if q[n]=0 and q[n+1]=1
    return 2;

    else
    return 3;
  }



   int retcarry(int x,int y)
   {
     if(x==1&&y==1)
     return 1;

     else
     return 0;
   }




   int retsum(int x,int y)
   {
     if(x==1&&y==1)
     return 0;

     if(x==0&&y==0)
     return 0;

     else
     return 1;
   }




   int complement(int br[5],int comp[5])
   {
       int i,carry=1,sum;

       for(i=0;i<5;i++)
       {  if(br[i]==1)
	  comp[i]=0;

	  else
	  comp[i]=1;
       }

       for(i=4;i>=0;i--)
       {
	  sum=retsum(comp[i],carry);
	  carry=retcarry(comp[i],carry);
	  comp[i]=sum;
       }
       return carry;
   }

      void substract(int ac[5],int comp[5])
   {
       int i,carry=0,sum;

	for(i=4;i>=0;i--)
       {
	 sum=rsum(ac[i],comp[i],carry);
	 carry=rcarry(ac[i],comp[i],carry);
	 ac[i]=sum;
       }
   }

       void add(int ac[5],int br[5])
   {
      int i,carry=0,sum;

	 for(i=4;i>=0;i--)
       {
	 sum=rsum(ac[i],br[i],carry);
	 carry=rcarry(ac[i],br[i],carry);
	 ac[i]=sum;
       }
   }


     void ashr(int ac[5],int qr[5])
  {
      int i,save;
      save=ac[4];

      for(i=3;i>=0;i--)
     {
       ac[i+1]=ac[i];
     }

      for(i=3;i>=0;i--)
     {
       qr[i+1]=qr[i];
     }
     qr[0]=save;


  }




  int rsum(int x,int y,int z)              //full adder sum logic
    {
      int a,s;

      a=(x*comp(y))+(y*comp(x));
      s=(a*comp(z))+(z*comp(a));

					  //returns x xor y xor z
      return s;
   }




   int rcarry(int x,int y,int z)          //full adder carry logic
   {
      int a,b,c;
      a=x*y;
      b=((x*(comp(y)))+(y*(comp(x))))*z;
      c=a+b;

      return c;                          //returns xy+ (x xor y)z
   }




  int comp(int x)
{
  if(x==0)
  return 1;

  else
  return 0;
}


 void evaluate(int x[],int y[])
 {
    int z=0,i,c=0,test=0,carry,sum;
    if(x[0]==1)
   {  test=1;


      carry=complement(y,y);

       for(i=4;i>=0;i--)
       {
	 x[i]=comp(x[i]);
       }

       for(i=4;i>=0;i--)
       {
	 sum=retsum(x[i],carry);
	 carry=retcarry(x[i],carry);
	 x[i]=sum;
       }

   }


    for(i=4;i>=0;i--)
    {
     z=z+(pow(c)*x[i]);
     c++;
    }
    c=0;
    for(i=4;i>=0;i--)
    {
     z=z+(pow(c)*y[i]);
     c++;
    }

     if(test==1)
     printf("\nresult:-%d",z);
     else
     printf("\nresult:%d",z);

 }

 int pow(int x)
 {
    int z=1,i;
    if(x==0)
    return 1;

    for(i=0;i<x;i++)
    {
      z=2*z;
    }
    return z;

 }

