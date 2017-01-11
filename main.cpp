/*   TETRIS GAME
Controls:
    A: Move left
    D: Move right
    S: Move down
    E: Rotate
*/
#include <iostream>
#include<time.h>
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<conio.h>

///define number of tetris object models and how many times an object can be rotated
#define NUMBER_OF_MODELS 7
#define NUMBER_OF_ROTATIONS 4

using namespace std;
///initialization of matrix, all values are 0
int a[50][50];
///x - tetris object model, ranges from 0 to 6
///p - incremented if first object is placed
///f - end game status
int x=0,p=0,f=0;

///colours matrix position based on x,y values
///x - value stored in current position
///      - 0 for empty space
///      - 1 for currently moving tetris object
///      - 2 for placed tetris object
///y - value ranging from 0 to 6 representing a color for each tetris object
void colour(int x,int y) ///ENUM POATE
{
    HANDLE hConsole;
    hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
///colours background blue then black after output
    if (x==0)
    {
        SetConsoleTextAttribute(hConsole , 17);
        cout<<x;
        SetConsoleTextAttribute(hConsole , 3);

    }
///sets a different text colour for each tetris object
    if(x==1)
    {
        switch(y)
        {
        case(0):
        {
            SetConsoleTextAttribute(hConsole ,14);
            cout<<x;
            break;
        }
        case(1):
        {
            SetConsoleTextAttribute(hConsole ,12);
            cout<<x;
            break;
        }
        case(2):
        {
            SetConsoleTextAttribute(hConsole , 2);
            cout<<x;
            break;
        }
        case(3):
        {
            SetConsoleTextAttribute(hConsole ,15);
            cout<<x;
            break;
        }
        case(4):
        {
            SetConsoleTextAttribute(hConsole , 10);
            cout<<x;
            break;
        }
        case(5):
        {
            SetConsoleTextAttribute(hConsole , 6);
            cout<<x;
            break;
        }
        case(6):
        {
            SetConsoleTextAttribute(hConsole ,13);
            cout<<x;
            break;
        }
        }
    }
///sets text colour to light blue
    if(x==2)
    {
        SetConsoleTextAttribute(hConsole , 3);
        cout<<x;
    }

}
///checks if a tetris object was placed above the displayed part
///of the matrix, if so game is lost
bool lose(int a[50][50],int n)
{
    for(int k=1; k<=n; k++)
        if(a[4][k]==2)return 0;

    return 1;
}
///n - displayed matrix number of lines
///m - displayed matrix number of columns
///verifies if there are lines of 2's and deletes them
void deleteLines(int a[50][50],int m,int n)
{
///assigns matrix number of lines to k
    int i,j,k=n;
///verifies starting from the bottom line upwards until
///it finds a line that should not be deleted
    while(k>0)
    {
        int ok=1;
        for(i=1; i<=m; i++)
            ///breaks from while loop
            if(a[k][i]!=2) ok=0;
        ///deletes line and moves all placed tetris objects downwards
        if(ok==1)
        {
            for(i=1; i<=m; i++)
                a[k][i]=0;

            for(i=k-1; i>0; i--)
            {
                for(j=1; j<=m; j++)
                    if(a[i][j]==2)
                    {
                        a[i][j]=0;
                        a[i+1][j]=2;
                    }
            }

        }
        else k--;
    }

}

///returns true if position of tetris object rotated e times is not colliding with another object
///k,l - position in  matrix where object position is created
///x - type of tetris object
///e - times object was rotated
bool shapeCond(int k,int x,int l,int e)
{
///assign values to variables based on e value to create position of tetris object
    int c,b,d,f;
    if(e==0)
    {
        c=0;
        b=1;
        f=-1;
        d=-1;
    }
    if(e==1)
    {
        c=1;
        b=0;
        f=-1;
        d=-1;
    }
    if(e==2)
    {
        c=0;
        b=-1;
        f=1;
        d=1;
    }
    if(e==3)
    {
        c=-1;
        b=0;
        f=1;
        d=1;
    }

///checks if position of x type object does not collide with another object
    if(x==0)
    {
        if( a[k][l]!=2 && a[k-f][l+d]!=2 && a[k+(d+f)][l-(d-f)]!=2 && a[k+d][l+f]!=2)
            return 1;
    }
    if(x==1)
    {
        if(a[k-f][l-d]!=2 && a[k][l]!=2 && a[k+d][l-f]!=2 && a[k+(d-f)][l+(d-f)]!=2)
            return 1;
    }
    if(x==2)
    {
        if(a[k+b][l+c]!=2 && a[k][l]!=2 && a[k+c][l+b]!=2 && a[k+2*c][l+2*b]!=2)
            return 1;
    }
    if(x==3)
    {
        if(a[k-b][l-c]!=2 && a[k][l]!=2 && a[k+c][l+b]!=2 && a[k+2*c][l+2*b]!=2)
            return 1;
    }
    if(x==4)
    {
        if(a[k][l]!=2 && a[k][l+1]!=2 && a[k+1][l]!=2 && a[k+1][l+1]!=2)
            return 1;
    }
    if(x==5)
    {
        if(a[k-c][l-b]!=2 && a[k][l]!=2 && a[k+b][l+c]!=2 && a[k+c][l+b]!=2)
            return 1;
    }
    if(x==6)
    {
        if(a[k-b][l-c]!=2 && a[k][l]!=2 && a[k+b][l+c]!=2 && a[k+2*b][l+2*c]!=2)
            return 1;
    }
///position collides
    return 0;
}
///creates tetris objects
///k,l - x,y position in matrix
///x - shape type
///e - number of rotations
void shape(int k,int x,int l,int e)
{
    ///assign values to variables based on e value to create position of tetris object
    int c,b,d,f;
    if(e==0)
    {
        c=0;
        b=1;
        f=0;
        d=1;
    }
    if(e==1)
    {
        c=1;
        b=0;
        f=1;
        d=0;
    }
    if(e==2)
    {
        c=0;
        b=-1;
        f=0;
        d=1;
    }
    if(e==3)
    {
        c=-1;
        b=0;
        f=1;
        d=0;
    }
///assigns 1's to x object's position
    if(x==0)
    {
        a[k][l]=1;
        a[k-f][l+d]=1;
        a[k+(d+f)][l-(d-f)]=1;
        a[k+d][l+f]=1;

    }
    if(x==1)
    {
        a[k-f][l-d]=1;
        a[k][l]=1;
        a[k+d][l-f]=1;
        a[k+(d+f)][l-(f-d)]=1;
    }
    if(x==2)
    {
        a[k+b][l+c]=1;
        a[k][l]=1;
        a[k+c][l+b]=1;
        a[k+2*c][l+2*b]=1;

    }
    if(x==3)
    {
        a[k-b][l-c]=1;
        a[k][l]=1;
        a[k+c][l+b]=1;
        a[k+2*c][l+2*b]=1;
    }
    if(x==4)
    {
        a[k][l]=1;
        a[k][l+1]=1;
        a[k+1][l]=1;
        a[k+1][l+1]=1;
    }
    if(x==5)
    {
        a[k-c][l-b]=1;
        a[k][l]=1;
        a[k+b][l+c]=1;
        a[k+c][l+b]=1;
    }
    if(x==6)
    {
        a[k-b][l-c]=1;
        a[k][l]=1;
        a[k+b][l+c]=1;
        a[k+2*b][l+2*c]=1;

    }

}
///places the current object, modifying its values to 2

void place(int a[50][50],int n,int m)
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
            if(a[i][j]==1)a[i][j]=2;
    }
}

///verifies if rotated object goes beyond displayed matrix edges
bool eLimit(int a[50][50],int m,int n)
{
    for(int i=5; i<=n; i++)
        for(int j=1; j<=m; j++)
            if(a[i][0]==1 || a[i][m+1]==1 || a[n+1][j]==1)return 0;

    return 1;

}

///verifies if object must stop
bool stop(int a[50][50],int n,int m)
{
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            ///object reached the top of a placed object
            if(a[i][j]==2 && a[i-1][j]==1)return 1;

    return 0;
}

///verifies if object reached the left edge of the displayed matrix
///or if it meets a placed object on its left side
bool leftCond(int n,int m,int a[50][50])
{
    int j=1;
    for(int i=1; i<=n; i++)
        if(a[i][j]==1) return 1;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            ///limit reached
            if(a[i][j]==2 && a[i][j+1]==1)return 1;

    return 0;

}

///verifies if object reached the right edge of the displayed matrix
///or if it meets a placed object on its right side
bool rightCond(int n,int m,int a[50][50])
{
    int j=m;
    for(int i=1; i<=n; i++)
        if(a[i][j]==1) return 1;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            ///limit reached
            if(a[i][j]==2 && a[i][j-1]==1)return 1;

    return 0;

}

///verifies if object reached bottom edge of the displayed matrix
bool bottomCond(int a[50][50],int n,int m)
{
    for(int j=1; j<=m; j++)
        if(a[n][j]==1)return 1;

    return 0;

}
///returns true if game is won
bool win(int a[50][50],int n,int m)
{
    for(int j=1; j<=m; j++)
        if(a[n][j]==2)return 0;
///no object on bottom line => game won
    return 1;

}
///updates the matrix and places the current object
void update(int a[50][50],int k,int x,int l,int e,int n,int m)
{
    for(int i=1; i<=n+1; i++)
    {
        for(int j=0; j<=m+1; j++)
        {
            ///assign values to either 0 or 2, this way we delete the object's old positon
            if(a[i][j]==2) a[i][j]=2;
            else a[i][j]=0;

        }
    }
    ///place new object positon
    shape(k,x,l,e);
    ///delete old display
    system("CLS");
    ///display matrix
    for(int i=5; i<=n; i++)
    {
        cout<<"\n";
        for(int j=1; j<=m; j++)
            colour(a[i][j],x);

    }
    ///sleep for 150 ms
    Sleep(150);

}
///n,m - displayed matrix size
///f - game ending status 0 - fail , 1 - win
///g - acts as a boolean for weather or not we should create the next tetris object
///p- verifies if first object was placed
///recursiv method which ends when game is lost or won
int game(int n,int m,int g,int f)
{
    ///char used in detecting key presses
    char c;
    ///object starts on first line and middle column
    int i,j,k=1,l,e;
    l=m/2;

    ///while there is no lose/win case
    while(lose(a,m) && f!=1)
    {
        ///time variables used in game timer
        clock_t time, st;
        st=clock();
        ///assign 0/2 values, delete old object
        for(i=1; i<=n+1; i++)
        {
            for(j=0; j<=m+1; j++)
            {
                if(a[i][j]==2) a[i][j]=2;
                else a[i][j]=0;

            }
        }
        ///if won condition is met increment f and end game
        if(win(a,n,m)==1 && p==1)
        {
            f+=1;
            system("CLS");
            for(i=5; i<=n; i++)
            {
                cout<<"\n";
                for(j=1; j<=m; j++)
                    colour(a[i][j],x);

            }
            cout<<"\n";
            break;
        }
        ///update tetris model and decrement g
        if(g==1)
        {
            x+=1;
            x=x%NUMBER_OF_MODELS;///7
            g=0;
            e=0;
        }
        ///create shape and delete display
        shape(k,x,l,e);
        system("CLS");
        ///display matrix
        for(i=5; i<=n; i++)
        {
            cout<<"\n";
            for(j=1; j<=m; j++)
                colour(a[i][j],x);

        }



        for(j=1; j<=m; j++)
            ///checks if object reached bottom edge
            if(a[n][j]==1 || stop(a,n,m)==1)
            {
                ///wait for user input before placing object
                while((clock()-st)/CLOCKS_PER_SEC<1)
                {
                    if (kbhit()!=0)
                    {
                        ///read key press
                        c=getch();
                        ///move left
                        if(c=='a' && leftCond(n,m,a)==0)
                        {
                            l--;
                            update(a,k,x,l,e,n,m);
                        }
                        ///move right
                        if(c=='d' && rightCond(n,m,a)==0)
                        {
                            l++;
                            update(a,k,x,l,e,n,m);
                        }
                    }
                }

                for(j=1; j<=m; j++)
                    ///checks if object reached bottom edge
                    if(a[n][j]==1 || stop(a,n,m)==1)
                    {
                        ///place object,check for lines to delete, update g and p variables and recalls method
                        place(a,n,m);
                        deleteLines(a,m,n);
                        g=1;
                        p=1;
                        game(n,m,g,f);
                    }

            }
        ///wait for user input
        while((clock()-st)/CLOCKS_PER_SEC<1 && bottomCond(a,n,m)!=1)
        {
            if (kbhit()!=0)
            {
                ///read key press
                c=getch();
                ///move left
                if(c=='a' && leftCond(n,m,a)==0)
                {
                    l--;
                    update(a,k,x,l,e,n,m);
                }
                ///move right
                if(c=='d' && rightCond(n,m,a)==0)
                {
                    l++;
                    update(a,k,x,l,e,n,m);
                }
                ///move down
                if(c=='s' && stop(a,n,m)==0)
                {
                    k++;
                    update(a,k,x,l,e,n,m);
                }
                ///rotate,check if next rotate doesn't collide
                if(c=='e' && stop(a,n,m)==0 && shapeCond(k,x,l,(e+1)%NUMBER_OF_ROTATIONS))///acum merge 4
                {
                    ///increment e
                    e = (e+1)%NUMBER_OF_ROTATIONS;
                    shape(k,x,l,e);
                    ///if edge is breached rotate back
                    if( eLimit(a,m,n)==0)
                    {
                        e--;
                        if(e==-1)e=3;
                    }
                    update(a,k,x,l,e,n,m);


                }

            }
        }
        ///no user input and bottom edge not reached => move down
        if(stop(a,n,m)==0 && bottomCond(a,n,m)!=1)
            k++;
    }
    ///return game status
    return f;
}


int main()
{
    int n,m,i=1,j,g=1;
    char c;
    ///start display
    while(i<2)
    {
        HANDLE hConsole;
        hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
        clock_t time, st;
        st=clock();


        cout<<"        TETRIS       "<<"\n"<<"\n";
        if(i==1)
        {
            SetConsoleTextAttribute(hConsole ,151);
            cout<<"PRES 'G' TO START GAME ";
            i--;
            SetConsoleTextAttribute(hConsole ,7);
            cout<<"\n";
        }
        else
        {
            SetConsoleTextAttribute(hConsole ,121);
            cout<<"PRES 'G' TO START GAME ";
            i++;
            SetConsoleTextAttribute(hConsole ,7);
            cout<<"\n";
        }
        while((clock()-st)/CLOCKS_PER_SEC<1)
            if (kbhit()!=0)
                c=getch();

        system("CLS");
        if(c=='g' || c=='G')
        {
            break;
        }


    }
    ///game menu
    cout<<"Choose map size:\n";
    cout<<"  Small: S\n";
    cout<<"  Medium:M\n";
    cout<<"  Large: L\n";
    cout<<"\n";
    cout<<"Controls:\n";
    cout<<"  A: Move left \n";
    cout<<"  D: Move right\n";
    cout<<"  S: Move down\n";
    cout<<"  E: Rotate\n";

    int s=0;
    while(s!=1)
    {
        ///assign matrix size based on user input and start game
        c=getch();
        if((c=='s' || c=='S') && f==0)
        {
            n=15;
            m=11;
            game(n,m,g,f);
            s=1;
        }
        if((c=='m' || c=='M') && f==0)
        {
            n=19;
            m=15;
            game(n,m,g,f);
            s=1;
        }
        if((c=='l' || c=='L') && f==0)
        {
            n=23;
            m=19;
            game(n,m,g,f);
            s=1;
        }
    }
    cout<<"\n";
    ///display result
    if(game(n,m,g,f)==1)
    {
        HANDLE hConsole;
        hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole , 14);
        cout<<"YOU WON!";
    }
    else
    {
        HANDLE hConsole;
        hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole , 12);
        cout<<"YOU LOST!";
    }


    return 0;
}
