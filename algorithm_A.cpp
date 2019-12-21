#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/
class stacks;
class neighbor;
void getneighbor(neighbor*,int ,int);
int chain(Board,char);
int scores(Board,char); 
class neighbor{
    public:
        neighbor(){  x=-1; y=-1;}
        friend void getneighbor(neighbor*,int ,int);
        friend int chain(Board,char);
        friend int scores(Board,char); 
        void set(int a,int b){ x=a;y=b;}
    private:
        int x;
        int y;
};
void getneighbor(neighbor* neighbors,int x,int y){
    if(x==0&&y==0){
        neighbors[0].set(x+1,y); neighbors[1].set(x,y+1);
    }         
    else if(x==0&&y==5){
         neighbors[0].set(x+1,y); neighbors[1].set(x,y-1);
    }
    else if(x==4&&y==0){
        neighbors[0].set(x-1,y); neighbors[1].set(x,y+1);
    }
    else if(x==4&&y==5){
        neighbors[0].set(x-1,y); neighbors[1].set(x,y-1);
    }
    else if(x==0){
        neighbors[0].set(x+1,y); neighbors[1].set(x,y+1); neighbors[2].set(x,y-1);
    }
    else if(x==4){
        neighbors[0].set(x-1,y); neighbors[1].set(x,y+1); neighbors[2].set(x,y-1);
    }
    else if(y==0){
        neighbors[0].set(x-1,y); neighbors[1].set(x,y+1); neighbors[2].set(x+1,y);
    }
    else if(y==5){
        neighbors[0].set(x+1,y); neighbors[1].set(x,y-1); neighbors[2].set(x-1,y);
    }
    else{
        neighbors[0].set(x+1,y); neighbors[1].set(x,y-1); neighbors[2].set(x-1,y); neighbors[3].set(x,y+1);
    }
}
class node{
    public:
        friend stacks;
        node(){};
        ~node(){};
        node(int a){
            next=NULL;
            data=a;
        }
    private:
        node* next;
        int data;
};
class stacks{
    public:
        stacks(){
           size=0;
           top=NULL;
        }
        ~stacks(){};
        bool isempty();
        void push(int);
        void pop();
        int Top(){
            return top->data;
        }
    private:
        node* top;
        int size;
};
bool stacks::isempty(){
    return (size==0);
}
void stacks::push(int x){
    size++;
    if(!top){
        top=new node(x);
        top->next=NULL;
    }
    else{
        node* tmp=new node(x);
        tmp->next=top;
        top=tmp;
    }
}
void stacks::pop(){
    if(isempty())return;
    node* tmp=top;
    top=top->next;
    delete tmp;
    tmp=NULL;
    size--;
}
int chain(Board board,char color){

    bool visited[5][6];
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            visited[i][j]=false;
        }
    }
    int length=0;
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            if(!visited[i][j] && board.get_orbs_num(i,j)==board.get_capacity(i,j)-1 && board.get_cell_color(i,j)==color){
                int n=0;
                stacks s;
                s.push(i*6+j);
                while(!s.isempty()){
                    int pos=s.Top();
                    s.pop();
                    visited[pos/6][pos%6]=true;
                    n++;
                    neighbor neighbors[4];
                    getneighbor(neighbors,pos/6,pos%6);
                    //cout<<pos/6<<" "<<pos%6<<",";
                    for(int k=0;k<4;k++){
                        if(!visited[neighbors[k].x][neighbors[k].y] &&neighbors[k].x!=-1 && neighbors[k].y!=-1 && board.get_cell_color(neighbors[k].x,neighbors[k].y)==color 
                        && board.get_orbs_num(neighbors[k].x,neighbors[k].y)==board.get_capacity(neighbors[k].x,neighbors[k].y)-1){
                            s.push(neighbors[k].x*6+neighbors[k].y);
                            
                        }
                    }
                    
                        
                }
                if(n>1){
                    length+=n*2;
                    //cout<<n<<"n"<<endl;
                }
                //cout<<endl;
            }
        }
    }
    //cout<<" lenghth"<<length<<endl;
    return length;
}
int maximum(int a,int b){
    return (a>b)? a:b;
}
class bestpoint{
    public:
        friend bestpoint minimax(Board&,int,bool,int,int,char,char); 
        friend void algorithm_A(Board, Player, int*);
        //friend bestpoint findbestscore(Board&,char,int,int);
    private:
        int x;
        int y;
        int bestvalue;
};
/*bestpoint findbestscore(Board & board, char enemycolor,int x,int y){
    
    bestpoint* best;
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            if(board.get_cell_color(i,j)!=enemycolor){
                Board thisround=board;
                Player p(color);
                thisround.place_orb(i,j,&p);
                int thisroundscore;
                
                thisroundscore=scores(thisround,color);
                
                if(best.value<thisroundscore){
                    best.bestvalue=thisroundscore;
                    best.x=i;
                    best.y=j;
                }
                if(best.bestvalue==10000)
                    break;
            } 
        }
        if(best.bestvalue==10000)
            break;
    }
    return best;

}*/

bestpoint minimax(Board& board ,int depth,bool ismax,int alpha,int beta,char color,char enemycolor){

    if(depth==7){
        bestpoint val;
        val.bestvalue=scores(board,color);
        return val;
    }
    if(ismax){
        bestpoint best;
        best.bestvalue=-10000;

        for(int i=0;i<5;i++){
            for(int j=0;j<6;j++){
                if(board.get_cell_color(i,j)!=enemycolor){
                    Board thisround=board;
                    Player p(color);
                    thisround.place_orb(i,j,&p);
                    bestpoint val;
                    val=minimax(thisround,depth+1,false,alpha,beta,color,enemycolor);
                    val.x=i;
                    val.y=j;
                    if(val.bestvalue>best.bestvalue){
                        best=val;
                    }
                    if(best.bestvalue>alpha){
                        alpha=best.bestvalue;
                    }
                    if(beta<=alpha){
                        break;
                    }
                }
                
            }
        }
           

        return best;
    }
    else{
        bestpoint best;
        best.bestvalue=10000;

        for(int i=0;i<5;i++){
            for(int j=0;j<6;j++){
                if(board.get_cell_color(i,j)!=color){
                    Board thisround=board;
                    Player p(enemycolor);
                    thisround.place_orb(i,j,&p);
                    bestpoint val;                    
                    val=minimax(thisround,depth+1,true,alpha,beta,color,enemycolor);
                    val.x=i;
                    val.y=j;

                    if(val.bestvalue<best.bestvalue){
                        best=val;
                    }
                    if(best.bestvalue<beta){
                        beta=best.bestvalue;
                    }
                    if(beta<=alpha){
                        break;
                    }
                }
            }
        }

        return best;
    }

    

}

int scores(Board board, char color){
    
    int score=0;
    int enemy_num=0;
    int my_num=0;

    char enemycolor=(color=='r')? 'b':'r';

    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            if(board.get_cell_color(i,j)==color){
                my_num+=board.get_orbs_num(i,j);
                bool flag=false;
                neighbor neighbors[4];
                getneighbor(neighbors,i,j);
                for(int k=0;k<4;k++){
                    if(neighbors[k].x!=-1 && neighbors[k].y!=-1 && board.get_cell_color(neighbors[k].x,neighbors[k].y)==enemycolor 
                    && board.get_orbs_num(neighbors[k].x,neighbors[k].y)==board.get_capacity(neighbors[k].x,neighbors[k].y)-1){
                        score-=5-board.get_capacity(i,j);
                        flag=true;
                    }
                }
                if(!flag){
                    if(board.get_capacity(i,j)==3)
                        score+=2;
                    else if(board.get_capacity(i,j)==2)
                        score+=3;
                    if(board.get_orbs_num(i,j)==board.get_capacity(i,j)-1)
                        score+=2;
                }
            }
            else if(board.get_cell_color(i,j)==enemycolor){
                enemy_num+=board.get_orbs_num(i,j);
            }
            
        }
    }
    score+=my_num;

    if(enemy_num==0 && my_num>1)
        return 10000;
    else if(my_num==0 && enemy_num>1)
        return -10000;

    int chainlength=chain(board,color);
    score+=chainlength;
    return score;
}

void algorithm_A(Board board, Player player, int index[]){

    // cout << board.get_capacity(0, 0) << endl;
    // cout << board.get_orbs_num(0, 0) << endl;
    // cout << board.get_cell_color(0, 0) << endl;
    // board.print_current_board(0, 0, 0);

    //////////// Random Algorithm ////////////
    // Here is the random algorithm for your reference, you can delete or comment it.
    //srand(time(NULL));
    int row, col;
    char color = player.get_color();
    
    Board thisround=board;
   /* while(1){
        row = rand() % 5;
        col = rand() % 6;
        if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    }*/
    char enemycolor=(color=='r')? 'b':'r';
    bestpoint best=minimax(thisround,1,true,-1000,10000,color,enemycolor);
    /*Player p(color);
    thisround.place_orb(row, col, &p);*/
    row=best.x;
    col=best.y;

    cout<<scores(thisround,color)<<endl;
    index[0] = row;
    index[1] = col;
}