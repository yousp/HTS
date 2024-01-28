// A Simple HTS Calculating System v0.1
//
// How To Use : Enter a number to calculate HTS (2 to input)
//
// Max Input Value : 100000(safe)
//
// Output:
// HTS

#include <stdio.h>
#include <inttypes.h>
#include <string.h>

// LCM calculating code starts..

#define DIGIT_MOD 1000000000
uint64_t num[100],digits=1;

void reset()
{
    memset(num,0,sizeof(uint64_t)*100);
    num[0]=1;
    digits=1;
}

uint64_t gcd(uint64_t a,uint64_t b)
{
    uint64_t A=a,B=b,C;
    while(B!=0)
    {
        C=B;
        B=A%B;
        A=C;
    }
    return A;
}

void multo(uint64_t a)
{
    uint64_t upper=0;
    for(uint64_t i=0;i<digits;i++)
    {
        num[i]=num[i]*a+upper;
        upper=num[i]/DIGIT_MOD;
        num[i]=num[i]%DIGIT_MOD;
    }
    if(upper!=0)
    {
        num[digits++]=upper;
    }
    while(num[digits-1]==0)
    {
        digits--;
    }
}

uint64_t gcdwith(uint64_t a)
{
    uint64_t mult=1,result=0;
    for(uint64_t i=0;i<digits;i++)
    {
        result=result+(mult*num[i])%a;
        result=result%a;
        mult=mult*DIGIT_MOD%a;
    }
    return gcd(a,result);
}

void print_large_num()
{
    printf("%I64u",num[digits-1]);
    for(uint64_t i=digits-2;i>=0;i--)
    {
        printf("%09I64u",num[i]);
    }
}
void fprint_large_num(FILE *f)
{
    fprintf(f,"%I64u",num[digits-1]);
    if(digits==1) return;
    for(uint64_t i=digits-1;i>0;i--)
    {
        fprintf(f,"%09I64u",num[i-1]);
    }
}

// HTS calculating code starts..

uint64_t Map[100001];
uint64_t yak[20001],len;
bool visited[100001];

void rev(int st,int nd)
{
    uint64_t t;
    while(st<nd)
    {
        t=Map[st];
        Map[st]=Map[nd-1];
        Map[nd-1]=t;
        st++;
        nd--;
    }
}

uint64_t calc_loop(uint64_t t,uint64_t n)
{
    if(visited[t]) return 1;
    uint64_t i,cnt=0;
    i=t;
    while(!visited[i])
    {
        visited[i]=true;
        i=Map[i];
        cnt++;
    }
    return cnt;
}


void calc_hts(uint64_t n)
{
    reset();
    memset(Map,0,sizeof(uint64_t) * 100001);
    memset(visited,0,sizeof(bool) * 100001);
    memset(yak,0,sizeof(uint64_t) * 20001);
    len=0;
    for(uint64_t i=1;i<=n;i++)
    {
        Map[i]=i;
    }
    for(uint64_t i=1;i*i<=n;i++)
    {
        if(n%i!=0) continue;
        yak[len++]=i;
        yak[len++]=n/i;
    }
    for(uint64_t i=2;i<len;i=i+2)
    {
        for(uint64_t j=yak[i];j<=n;j=j+yak[i])
        {
            rev(j-yak[i]+1,j+1);
        }
    }
    for(uint64_t i=len-1;i>1;i=i-2)
    {
        for(uint64_t j=yak[i];j<=n;j=j+yak[i])
        {
            rev(j-yak[i]+1,j+1);
        }
    }
    for(uint64_t j=yak[1];j<=n;j=j+yak[1])
    {
        rev(j-yak[1]+1,j+1);
    }
    uint64_t t;
    for(uint64_t i=1;i<=n;i++)
    {
        t=calc_loop(i,n);
        if(t!=1)
        {
            multo(t/gcdwith(t));
        }
    }
}

int main()
{
    uint64_t n;
    FILE *f;
    f=fopen("HTSResult.txt","w");
    scanf("%I64u",&n);
    for(int i=2;i<=n;i++)
    {
        fprintf(f,"Result of %I64u : ",i);
        calc_hts(i);
        fprint_large_num(f);
        fprintf(f,"\n");
    }
    fclose(f);
    return 0;
}
