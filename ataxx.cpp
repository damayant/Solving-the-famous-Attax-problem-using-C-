#include<iostream>
#include <limits.h>
#include<string.h>
#include<cmath>
#include <algorithm>
#include <vector>
#include<stack>


using namespace std;
char global[9][9];
char color,state;
int d,player,counter=0;
char undo_board [500][9][9] ;

//Function to check if there is any of the white/black left on board
bool Score(char (&p_board)[9][9],int &n)
{
    int white_score,black_score;
    bool flag;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if((p_board[i][j]=='w'))
            {
                white_score++;

                flag= true;
            }
            if((p_board[i][j]=='b'))
            {
                black_score++;
                flag=true;
            }
            else if ((white_score==0)||(black_score==0))
            {

                flag=false;
            }

        }
    }
    return  flag;
}

//Function to calculate individual scores
int playerscores(char (&p_board)[9][9],int &n,char color)
{
    int scores,white_score,black_score;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if((p_board[i][j]=='w'))
            {
                white_score++;
            }

            if((p_board[i][j]=='b'))
            {
                black_score++;
            }
            int total=white_score+black_score;

            if(color=='w')
            {
                scores=(total-black_score);

            }
            if(color=='b')
            {
                scores=(total-white_score);
            }
        }
    }
    return scores;
}

//Function to check the gameover condition which calls the Score() also
bool gameover(int &n , char (&p_board)[9][9],char color)
{
    bool flag1;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if((Score(p_board,n)!=false))
            {
                if((p_board[i][j]!='e'))
                {
                    flag1= false;
                }
                else
                {
                    flag1=true ;
                }

            }
        }
    }
    return flag1 ;
}

//Function to extract the co-ordinates of the from & to points
void retrieve_points(int number,int &fx,int &fy,int &tx,int &ty)
{

    fx=((number/1000)-1);
    number=(number%1000);
    fy=((number/100)-1);
    number=(number%100);
    tx=(number/10)-1;
    number=(number%10);
    ty=(number/1)-1;
}

//Function for copying the contents of one board to another
void Copy(int &n,char (&cboard)[9][9],char p_board[9][9])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cboard[i][j]=p_board[i][j];
        }
    }
}


int undoCopy(int &n,char (&undo_board)[500][9][9],char p_board[9][9])
{
    counter++;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {

            undo_board[counter][i][j]=p_board[i][j];
        }
    }
    return counter;
}


//Function to display
void display(char (&p_board)[9][9],int &n)
{
    for (int i=0; i < n; i++)
    {
        for (int j=0; j < n; j++)
        {
            cout << p_board[i][j] << "\t";
        }
        cout << endl;
    }

}

void undo_display(char (&undo_board)[500][9][9],char (&p_board)[9][9],int &n,int &counter)
{
        for (int i=0; i < n; i++)
        {
            for (int j=0; j < n; j++)
            {
                cout << undo_board[counter-1][i][j] ;
                p_board[i][j]=undo_board[counter-1][i][j];
            }
            cout << endl;
        }
}


//Function to check the jump condition
bool jump(char (&p_board)[9][9],int fx,int fy,int tx, int ty,char color)
{

    for(int i=fx-2;i<fx+3;i++)
    {
        for(int j=fy-2;j<fy+3;j++)
        {
            if((p_board[tx][ty]='e'))
            {
                if(p_board[tx][ty]!=color)
                {
                    return true;
                }
            }
            else
                cout<<"Error";
        }
    }
    return false;
}

//Function to check the duplicate condition
bool duplicate(char (&p_board)[9][9],int fx,int fy,int tx,int ty,char color)
{
    for(int i=fx-1;i<fx+2;i++)
    {
        for(int j=fy-1;j<fy+2;j++)
        {
            if((tx==i && ty==j))
            {
                if(p_board[tx][ty]!=color)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

//Function to check all the possible moves which calls the duplicate() and jump()
bool LegalMove(char (&p_board)[9][9],int fx,int fy,int tx, int ty,char color)
{
    bool flag;
    if ((p_board[tx][ty]!='x'))
    {
        if((p_board[tx][ty]!='w')||(p_board[tx][ty]!='b'))
        {

            if (duplicate(p_board,fx,fy,tx,ty,color)==true)
            {
                flag= true;

            }



            if(jump(p_board,fx,fy,tx,ty,color)==true)
            {
                flag= true;

            }

            else
                flag= false;

        }

    }

    return flag  ;
}


//Function to check the capture conditions
void capture(char (&p_board)[9][9],int tx, int ty,char color)
{
    for(int i=tx-1;i<=tx+1;i++)
    {
        for(int j=ty-1;j<=ty+1;j++)
        {
            if(p_board[i][j]!='x')
            {
                if(p_board[i][j]!='e')
                {
                    p_board[i][j]=color;
                }
            }
        }
    }
}


//Function to make the moves
bool MakeMove(char (&p_board)[9][9],int fx,int fy,int tx,int ty,char color)
{
    bool flag;
    if ((p_board[tx][ty]!='x'))
    {
        if((p_board[tx][ty]!='w')||(p_board[tx][ty]!='b'))
        {
            if (duplicate(p_board,fx,fy,tx,ty,color)==true)
            {
                if(p_board[tx][ty]=='e')
                {
                    p_board[tx][ty]=color;
                    capture(p_board,tx,ty,color);
                    flag=true;
                }
            }


            else if(jump(p_board,fx,fy,tx,ty,color)==true)
            {
                if(p_board[tx][ty]=='e')
                {
                    p_board[tx][ty]=color;
                    p_board[fx][fy]='e';
                    capture(p_board,tx,ty,color);
                    flag=true;
                }
            }
        }
    }

    return flag;
}

//Function to form the possible movelists
vector<int> MoveList(char (&p_board)[9][9],int n,char color)
{
    vector<int> mlist;

    int x1,y1,x2,y2;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if((p_board[i][j]!='x'))
            {
                if( (p_board[i][j]==color))
                {
                    if(i-2<0)
                    {
                        x1 = 0;
                    }
                    else
                    {
                        x1 = i-2;
                    }

                    if(i+2>n)
                    {
                        x2 = n;
                    }
                    else
                    {
                        x2 = i+2;
                    }



                    if(j-2<0)
                    {
                        y1 = 0;
                    }
                    else
                    {
                        y1 = j-2;
                    }

                    if(j+2>n)
                    {
                        y2 = n;
                    }
                    else
                    {
                        y2 = j+2;
                    }
                    for(int x=x1;x<=x2;x++)
                    {
                        for(int y=y1;y<=y2;y++)
                        {
                            if(p_board[x][y]=='e')
                            {
                                int vala=(1000*(i+1))+(100*(j+1))+(10*(x+1))+(y+1);
                                mlist.push_back(vala);
                            }
                        }
                    }
                }
            }
        }
    }
    return mlist;
}


vector<int> MoveListb(char (&p_board)[9][9],int n,char color)
{
    vector<int> mlistb;

    int x1,y1,x2,y2;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if((p_board[i][j]!='x'))
            {
                if(p_board[i][j]==(color=='b'))
                {
                    if(i-2<0)
                    {
                        x1 = 0;
                    }
                    else
                    {
                        x1 = i-2;
                    }

                    if(i+2>n)
                    {
                        x2 = n;
                    }
                    else
                    {
                        x2 = i+2;
                    }



                    if(j-2<0)
                    {
                        y1 = 0;
                    }
                    else
                    {
                        y1 = j-2;
                    }

                    if(j+2>n)
                    {
                        y2 = n;
                    }
                    else
                    {
                        y2 = j+2;
                    }
                    for(int x=x1;x<=x2;x++)
                    {
                        for(int y=y1;y<=y2;y++)
                        {
                            if(p_board[x][y]=='e')
                            {
                                int valb=(1000*(i+1))+(100*(j+1))+(10*(x+1))+(y+1);
                                mlistb.push_back(valb);
                            }
                        }
                    }
                }
            }
        }
    }
    return mlistb;
}

vector<int> MoveLista(char (&p_board)[9][9],int n,char color)
{
    vector<int> mlista;

    int x1,y1,x2,y2;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if((p_board[i][j]!='x'))
            {
                if(p_board[i][j]==(color=='a'))
                {
                    if(i-2<0)
                    {
                        x1 = 0;
                    }
                    else
                    {
                        x1 = i-2;
                    }

                    if(i+2>n)
                    {
                        x2 = n;
                    }
                    else
                    {
                        x2 = i+2;
                    }



                    if(j-2<0)
                    {
                        y1 = 0;
                    }
                    else
                    {
                        y1 = j-2;
                    }

                    if(j+2>n)
                    {
                        y2 = n;
                    }
                    else
                    {
                        y2 = j+2;
                    }
                    for(int x=x1;x<=x2;x++)
                    {
                        for(int y=y1;y<=y2;y++)
                        {
                            if(p_board[x][y]=='e')
                            {
                                int vala=(1000*(i+1))+(100*(j+1))+(10*(x+1))+(y+1);
                                mlista.push_back(vala);

                            }
                        }
                    }
                }
            }
        }
    }
    return mlista;
}





int children(vector<int> a)
{
    return a.size();
}





int negamaxA(int (&n),char (&p_board)[9][9],int depth, int alpha,int beta, char color)
{
    int fx,fy,tx,ty;

    if((depth = 0)||(gameover(n,p_board,(color=='w'))==true))
    {
        int scr=playerscores(p_board,n,(color=='w'));
        return scr;
    }

    vector <int> childNodes= MoveLista(p_board,n,color);
    int no=children(childNodes);
    int bestValue =-INFINITY ;


    for(int i=0;i<no;i++)
    {
        int possible_moves=childNodes.at(i);
        retrieve_points(possible_moves, fx,fy,tx,ty);

        LegalMove(p_board, fx, fy,tx, ty,color);
        MakeMove(p_board,fx,fy,tx,ty,color);


        int v = -negamaxA(n,p_board, d, -beta, -alpha, color );
        bestValue = max(bestValue,v);
        alpha = max(alpha,v);
        if(alpha>= beta)
        {
            break;
        }
    }
    return bestValue;
}


int negamaxB(int (&n),char (&p_board)[9][9],int depth, int alpha,int beta, char color)
{
    int fx,fy,tx,ty;

    if((depth = 0)||(gameover(n,p_board,(color=='b'))==true))
    {
        int scr=playerscores(p_board,n,(color=='b'));
        return scr;
    }

    vector <int> childNodesb= MoveListb(p_board,n,color);
    int nob=children(childNodesb);
    int bestValueb =-INFINITY ;


    for(int i=0;i<nob;i++)
    {
        int possible_movesb=childNodesb.at(i);
        retrieve_points(possible_movesb, fx,fy,tx,ty);

        LegalMove(p_board, fx, fy,tx, ty,color);
        MakeMove(p_board,fx,fy,tx,ty,color);


        int v = -negamaxB(n,p_board, d, -beta, -alpha, color );
        bestValueb = max(bestValueb,v);
        alpha = max(alpha,v);
        if(alpha>= beta)
        {
            break;
        }
    }
    return bestValueb;
}


int main()
{

    char f,t;

    char p_board[9][9],board[9][9];
    int alpha=INT_MAX, beta=INT_MIN;

    cout<<"Welcome to Ataxx"<<endl;
    cout<<"After setting up the board or after each move select the player by pressing w  OR  b unless the player turn comes automatically" <<endl;
    


    while(true)
    {
        cin>>state;

        switch(state)
        {


            case 'i' :
                char s;
                int n;

                cin>>n;
                cin>>s;

                if(s=='s')
                {
                    for (int i=0; i < n; i++)
                    {
                        for (int j=0; j < n; j++)
                        {
                            cin>> p_board[i][j];
                        }
                        cout << endl;
                    }

                    display(p_board,n);

                    undoCopy(n,undo_board,p_board);

                }
                break;




            case 'q' :
                exit(0);
                break;


            case 'd' :
                cin>>d;
                break;


            case 'u':
                cout<<"undo-ing:"<<endl;
                undo_display(undo_board,p_board,n,counter);
                cin>>state;
                break;











            case 'b' :
                color='b';
                cout<<"Black plays"<<endl;

                char type1;
                cin>>type1;

                switch(type1)
            {

              case 'q' :
                  exit(0);
                  break;


              case 'd' :
                  cin>>d;
                  break;


              case 'u':
                  cout<<"undo-ing:"<<endl;
                  undo_display(undo_board,p_board,n,counter);
                  cin>>state;
                  break;

                case 'm':

                    color='b';
                    int ufx,ufy,utx,uty,fx,fy,tx,ty;
                    cin>>f>>ufx>>t>>utx;
                    ufy=(int(f)-96);
                    uty=(int(t)-96);
                    fx=n-ufx;
                    fy=ufy-1;
                    tx=n-utx;
                    ty=uty-1;

                    LegalMove(p_board,fx,fy,tx,ty,color);
                    MakeMove(p_board, fx, fy, tx, ty, color);
                    display(p_board, n);

                    undoCopy(n,undo_board,p_board);

                    gameover(n,p_board,color);

                    break;





                case 'g':
                    player=-1;
                    cout<<"The AI plays:"<<endl;
                    vector<int> nodesb;
                    nodesb=MoveList(p_board,n,color);
                    vector<int>storeb;
                    int bestb=-1000,indexb=0;
			
		int ab1=nodesb.size();

                    if(nodesb.size()>0)
                    {
                        for(int i=0;i<nodesb.size();i++)
                        {
                            int scb = nodesb.at(i);
                            retrieve_points(scb,fx,fy,tx,ty);
                            Copy(n,board,p_board);
                            LegalMove(board, fx,fy, tx, ty, color);
                            MakeMove(board,fx,fy,tx,ty,color);
                            Copy(n,global,board);
                            int getvalueb=negamaxB(n,board, d, alpha, beta,color);
                            storeb.push_back(getvalueb);
                            //cout<<"after negamax"<<endl;
                            //cout<<&storeb;
                            if(getvalueb>bestb)
                            {
                                bestb=getvalueb;
                                indexb=i;
                            }

                        }

                        int gotmoveb=nodesb.at(indexb);
                        Score(p_board,n);
                        retrieve_points(gotmoveb,fx,fy,tx,ty);
                        LegalMove(p_board, fx,fy, tx, ty, color);
                        MakeMove(p_board, fx, fy, tx, ty, color);
                        //cout<<"after negamax"<<endl;
                       cout<<fx<<","<<fy<<"-->>"<<tx<<","<<ty<<endl;
                       cout<<"Alpha-Beta calls:"<<ab1<<endl;
			cout<<"Depth:"<<d<<endl;
			 display(p_board,n);
                        player=player*(-1);

                        //counter++;
                        undoCopy(n,undo_board,p_board);

                        break;
                   //     cin>>state;

                    }



            }



            case 'w' :
                color='w';
                cout<<"White plays"<<endl;

                char type;
                cin>>type;

                switch(type)
            {

              case 'q' :
                  exit(0);
                  break;


              case 'd' :
                  cin>>d;
                  break;
                 // cin>>state;


              case 'u':
                  cout<<"undo-ing:"<<endl;
                  //cout<<endl;
                  undo_display(undo_board,p_board,n,counter);
                  cin>>state;
                  break;

                case 'm':

                    color='w';
                    int ufx,ufy,utx,uty,fx,fy,tx,ty;
                    cout<<"white plays"<<endl;
                    cin>>f>>ufx>>t>>utx;
                    ufy=(int(f)-96);
                    uty=(int(t)-96);
                    fx=n-ufx;
                    fy=ufy-1;
                    tx=n-utx;
                    ty=uty-1;

                    LegalMove(p_board,fx,fy,tx,ty,color);
                    MakeMove(p_board, fx, fy, tx, ty, color);
                    display(p_board, n);

                    //counter++;
                    undoCopy(n,undo_board,p_board);

                    gameover(n,p_board,color);
                    break;

                 //   cin>>state;


                case 'g':
                    player=1;
                    cout<<"The AI plays:"<<endl;
                    vector<int> nodes;
                    nodes=MoveList(p_board,n,color);
                    vector<int>store;
                    int best=-1000,index=0;

		int n2=nodes.size();			

                    if(nodes.size()>0)
                    {
                        for(int i=0;i<nodes.size();i++)
                        {
                            int sc = nodes.at(i);
                            retrieve_points(sc,fx,fy,tx,ty);
                            Copy(n,board,p_board);
                            //cout<<"in progress"<<endl;
                            LegalMove(board, fx,fy, tx, ty, color);
                            MakeMove(board,fx,fy,tx,ty,color);
                          //  cout<<fx<<","<<fy<<"-->>"<<tx<<","<<ty<<endl;
                            //display(p_board,n);
                            Copy(n,global,board);
                            int getvalue=negamaxA(n,board, d, alpha, beta,color);
                            //cout<<"after negamax"<<endl;
                            //counter++;
                            store.push_back(getvalue);
                            //cout<<"after negamax"<<endl;
                            //cout<<&store;
                            if(getvalue >best)
                            {
                                best=getvalue;
                                index=i;
                            }

                        }

                        int gotmove=nodes.at(index);
                        Score(p_board,n);
                        retrieve_points(gotmove,fx,fy,tx,ty);
                        LegalMove(p_board, fx,fy, tx, ty, color);
                        MakeMove(p_board, fx, fy, tx, ty, color);
                        //cout<<"after negamax"<<endl;
                        cout<<fx<<","<<fy<<"-->>"<<tx<<","<<ty<<endl;
			cout<<"Alpha Beta calls:"<<n2<<endl;
			cout<<"Depth :"<<d<<endl;			

                        display(p_board,n);
                        player=player*(-1);

                        //counter++;
                        undoCopy(n,undo_board,p_board);

                        break;
                    //    cin>>state;

                    }
            }



        }


    }
}
