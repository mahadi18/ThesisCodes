#include <bits/stdc++.h>
#include <stdlib.h>
#include <math.h>
#include <set>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
vector<int>pos[32];
vector<int>f1;
vector<int>box;
vector<int>errPos;
vector<int>errorBitPostion;
vector<int>genErr;
vector<int>errorRows;
int correct=0, wrong=0;
int totalCorrect=0, totalWrong=0;

int ham[4][8]=
{
    {1, 1, 0, 1, 1, 0, 1, 0},
    {1, 0, 1, 1, 0, 1, 1, 0},
    {0, 1, 1, 1, 0, 0, 0, 1},
    {0, 0, 0, 0, 1, 1, 1, 1}

};

int k;
int row;
int columnParity[100];
int xerror[256],cerror[100],xCorrect[256];
bool rowError[100];
int x[256];
int sp[8];
int sc[100];
int DED[100];
int Oi[100];
int parity[8]= {0,0,0,0,0,0,0,0};

void errorDetection()
{
    errorBitPostion.clear();
    errorRows.clear();

    for(int i=0, j=5*row-1; i<row; i++)
    {
        int ix = i*8;
        cerror[5*row-1 - j--] = xerror[ix] ^ xerror[ix+1] ^ xerror[ix+3] ^ xerror[ix+4] ^ xerror[ix+6];
        cerror[5*row-1 - j--] = xerror[ix] ^ xerror[ix+2] ^ xerror[ix+3] ^ xerror[ix+5] ^ xerror[ix+6];
        cerror[5*row-1 - j--] = xerror[ix+1] ^ xerror[ix+2] ^ xerror[ix+3] ^ xerror[ix+7];
        cerror[5*row-1 - j--] = xerror[ix+4] ^ xerror[ix+5] ^ xerror[ix+6] ^ xerror[ix+7];
        cerror[5*row-1 - j--] = xerror[ix] ^ xerror[ix+1] ^ xerror[ix+2] ^ xerror[ix+3] ^ xerror[ix+4] ^ xerror[ix+5] ^ xerror[ix+6] ^ xerror[ix+7];

    }

    int parityError[8]= {0,0,0,0,0,0,0,0};
    for(int i=0; i<k; i++)
    {
        if(xerror[i]==1) parityError[i%8]++;
    }
    for(int i=0; i<8; i++)
    {
        if(parityError[i]%2==0) parityError[i]=0;
        else parityError[i]=1;
    }



    /************* Print Error Matrix ***********/
    /*cout<<endl;

    for(int i = 0,temp=0,j=0; i<k; i++)
    {
        if(i%8==0) cout<<" || ";
        cout<<xerror[i]<<" ";
        if((i+1)%8==0)
        {
            cout<<" || ";
            for(; j<temp+5; j++)
                cout<<cerror[j]<<" ";
            temp=temp+5;
            cout<<" || ";
            cout<<endl;

        }
    }
    cout<<" || ";
    for(int i=0; i<8; i++)
        cout<<parityError[i]<<" ";
    cout<<" ||            ||";

    cout<<endl;

    /**********sp and sc calculation***********/
    for(int i=0; i<8; i++)
    {
        sp[i] = abs(parity[i] - parityError[i]);
    }

    /*cout<<"\n\nSP =   ";
    for(int i=0; i<8; i++)
    {
        cout<<sp[i]<<"   ";
    }
    cout<<endl;*/

    for(int i=0; i<5*row; i++)
    {
        sc[i] = columnParity[i] ^ cerror[i];
    }

    /*cout<<"";

    cout<<"\nSC = ";
    for(int i=0; i<5*row; i++)
    {
        if(i%5==0) cout<<"  ";
        cout<<sc[i]<<" ";
    }
    cout<<endl<<"\n\n";*/




    /********Double error detection**********/

    int flag4 = 0,pp[row];
    memset(pp, 0, sizeof(pp));//here pp array is the first 4 bit of any 1

    for(int i = 0; i<row; i++)
    {
        int j;
        for( j = 0; j<4; j++)
        {

            if (sc[i*5+j]==1)
            {
                flag4 = 1;
                pp[i]=1;
                j=4;
                break;
            }
        }

        if (flag4 == 1 && sc[j+i*5]== 0)
            DED[i]= 1;

        else if (flag4==1 && sc[j+i*5]== 0)
        {
            DED[i]=0;
        }

        Oi[i]=sc[j+i*5];
        //cout << "oi "<< i << "  value "<<Oi[i]<<endl;

        flag4=0;
    }

    /**************** Error Correction ******************/

    for(int i=0; i<k; i++)
    {
        xCorrect[i] = xerror[i];  // Initializing correction array with error bits.
    }

    for(int i=0; i<row; i++)
    {
        if(DED[i]==1)
        {
            for(int j=0; j<8; j++)
            {
                if(sp[j]==1)
                {
                    pos[i].push_back(j);
                }
            }
        }

    }

    /*@now*/
    int numOfErrorRow = 0, c=0;


    for(int i=0; i<20;  )
    {
        c++;
        for(int j=i; j<=i+4; j++)
        {
            if(sc[j]==1)
            {
                numOfErrorRow++;
                errorRows.push_back(i%4);
                break;
            }
        }
        i=c*5;
    }


    /* to print the Rows where error occurred */
//    cout<<"numOfErrorRow = " <<numOfErrorRow<<endl;
//    for(int i=0; i<errorRows.size(); i++)
//        cout<<"errorRows[i] = " <<errorRows[i]<<endl;

    //cout<<"errorRows.size() = "<<errorRows.size()<<endl;

    int total=0;
    for(int numOfRowToCheck=0; numOfRowToCheck<errorRows.size(); numOfRowToCheck++)
    {
        int i = errorRows[numOfRowToCheck];
        bool errorInOddNumOfBitsInARow = false; // error in odd/even bits in a row. (ok)
        if(sc[i*5+4]==1) errorInOddNumOfBitsInARow=true;

        //cout<<"errorInOddNumOfBitsInARow = "<<errorInOddNumOfBitsInARow<<endl;

        int fourBitsOfSC[4];
        int hamCodeSC[4];

        //cout<<"fourBitsOfSC = ";
        for(int fb=0; fb<4; fb++)
        {
            fourBitsOfSC[fb] = sc[i*5+fb];
            //cout<<fourBitsOfSC[fb]<<" ";
        }
        //cout<<endl;
        if(errorInOddNumOfBitsInARow) /* odd number bits are error in this row */
        {

            /* Look for single Error in a Row */
            for(int se=0; se<8; se++)
            {
                //cout<<"Ham Generated SC: ";
                for(int hamCol=se, hamRow=0; hamRow<4; hamRow++)
                {
                    hamCodeSC[hamRow] = ham[hamRow][hamCol];
                    //cout<<hamCodeSC[hamRow]<<" ";
                }
                //cout<<endl;
                int same=0;
                for(int j=0; j<4; j++)
                {
                    if(fourBitsOfSC[j] == hamCodeSC[j])
                    {
                        same++;
                    }
                }

                if(same==4)
                {
                    errorBitPostion.push_back(i*8+se);
//                    cout<<"CORRECTION = "<<i*8+se<<endl;

                    total++;
                    if(total==errorRows.size())
                        goto CORRECTION;
                    else
                        goto DOWN;
                }
            }

            /* Look for Triple Error in a Row */
            for(int col1=0; col1<6; col1++)
            {
                for(int col2=col1+1; col2<7; col2++)
                {
                    for(int col3=col2+1; col3<8; col3++)
                    {
                        //cout<<"Ham Generated Sc: ";
                        for(int hamRow=0; hamRow<4; hamRow++)
                        {
                            hamCodeSC[hamRow] = ham[hamRow][col1] ^ ham[hamRow][col2] ^ ham[hamRow][col3];
                            //cout<<hamCodeSC[hamRow]<<" ";
                        }
                        //cout<<endl;
                        int same=0;
                        for(int j=0; j<4; j++)
                        {
                            if(fourBitsOfSC[j] == hamCodeSC[j])
                            {
                                same++;
                            }
                        }

                        if(same==4)
                        {
                            errorBitPostion.push_back(i*8+col1);
                            errorBitPostion.push_back(i*8+col2);
                            errorBitPostion.push_back(i*8+col3);
//                            cout<<"CORRECTION = "<<i*8+col1<<endl;
//                            cout<<"CORRECTION = "<<i*8+col2<<endl;
//                            cout<<"CORRECTION = "<<i*8+col3<<endl;
                            total++;
                            if(total==errorRows.size())
                                goto CORRECTION;
                            else
                                goto DOWN;
                        }
                    }
                }
            }

            /* Look for Five Errors in a row */
            for(int col1=0; col1<4; col1++)
            {
                for(int col2=col1+1; col2<5; col2++)
                {
                    for(int col3=col2+1; col3<6; col3++)
                    {
                        for(int col4=col3+1; col4<7; col4++)
                        {
                            for(int col5=col4+1; col5<8; col5++)
                            {
                                for(int hamRow=0; hamRow<4; hamRow++)
                                {
                                    hamCodeSC[hamRow] = ham[hamRow][col1] ^ ham[hamRow][col2] ^ ham[hamRow][col3] ^ ham[hamRow][col4] ^ ham[hamRow][col5];
                                    //cout<<hamCodeSC[hamRow]<<" ";
                                }

                                int same=0;
                                for(int j=0; j<4; j++)
                                {
                                    if(fourBitsOfSC[j] == hamCodeSC[j])
                                    {
                                        same++;
                                    }
                                }

                                if(same==4)
                                {
                                    errorBitPostion.push_back(i*8+col1);
                                    errorBitPostion.push_back(i*8+col2);
                                    errorBitPostion.push_back(i*8+col3);
                                    errorBitPostion.push_back(i*8+col4);
                                    errorBitPostion.push_back(i*8+col5);
                                    total++;
                                    if(total==errorRows.size())
                                        goto CORRECTION;
                                    else
                                        goto DOWN;
                                }
                            }
                        }
                    }
                }
            }

            /* Look for Seven error in a row */
            for(int col1=0; col1<2; col1++)
            {
                for(int col2=col1+1; col2<3; col2++)
                {
                    for(int col3=col2+1; col3<4; col3++)
                    {
                        for(int col4=col3+1; col4<5; col4++)
                        {
                            for(int col5=col4+1; col5<6; col5++)
                            {
                                for(int col6=col5+1; col6<7; col6++)
                                {
                                    for(int col7=col6+1; col7<8; col7++)
                                    {
                                        for(int hamRow=0; hamRow<4; hamRow++)
                                        {
                                            hamCodeSC[hamRow] = ham[hamRow][col1] ^ ham[hamRow][col2] ^ ham[hamRow][col3] ^ ham[hamRow][col4] ^ ham[hamRow][col5] ^ ham[hamRow][col6] ^ ham[hamRow][col7];
                                            //cout<<hamCodeSC[hamRow]<<" ";
                                        }

                                        int same=0;
                                        for(int j=0; j<4; j++)
                                        {
                                            if(fourBitsOfSC[j] == hamCodeSC[j])
                                            {
                                                same++;
                                            }
                                        }

                                        if(same==4)
                                        {
                                            errorBitPostion.push_back(i*8+col1);
                                            errorBitPostion.push_back(i*8+col2);
                                            errorBitPostion.push_back(i*8+col3);
                                            errorBitPostion.push_back(i*8+col4);
                                            errorBitPostion.push_back(i*8+col5);
                                            errorBitPostion.push_back(i*8+col6);
                                            errorBitPostion.push_back(i*8+col7);
                                            total++;
                                            if(total==errorRows.size())
                                                goto CORRECTION;
                                            else
                                                goto DOWN;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        else
        {
            /* Look for two errors in a row */
            for(int col1=0; col1<7; col1++)
            {
                for(int col2=col1+1; col2<8; col2++)
                {
                    for(int hamRow=0; hamRow<4; hamRow++)
                    {
                        hamCodeSC[hamRow] = ham[hamRow][col1] ^ ham[hamRow][col2];
                        //cout<<hamCodeSC[hamRow]<<" ";
                    }

                    int same=0;
                    for(int j=0; j<4; j++)
                    {
                        if(fourBitsOfSC[j] == hamCodeSC[j])
                        {
                            same++;
                        }
                    }

                    if(same==4)
                    {
                        errorBitPostion.push_back(i*8+col1);
                        errorBitPostion.push_back(i*8+col2);
//                            cout<<"CORRECTION = "<<i*8+col1<<endl;
//                            cout<<"CORRECTION = "<<i*8+col2<<endl;
                        total++;
                        if(total==errorRows.size())
                            goto CORRECTION;
                        else
                            goto DOWN;
                    }
                }
            }

            /* Look for four errors in a row*/
            for(int col1=0; col1<5; col1++)
            {
                for(int col2=col1+1; col2<6; col2++)
                {
                    for(int col3=col2+1; col3<7; col3++)
                    {
                        for(int col4=col3+1; col4<8; col4++)
                        {
                            for(int hamRow=0; hamRow<4; hamRow++)
                            {
                                hamCodeSC[hamRow] = ham[hamRow][col1] ^ ham[hamRow][col2] ^ ham[hamRow][col3] ^ ham[hamRow][col4];
                                //cout<<hamCodeSC[hamRow]<<" ";
                            }

                            int same=0;
                            for(int j=0; j<4; j++)
                            {
                                if(fourBitsOfSC[j] == hamCodeSC[j])
                                {
                                    same++;
                                }
                            }

                            if(same==4)
                            {
                                errorBitPostion.push_back(i*8+col1);
                                errorBitPostion.push_back(i*8+col2);
                                errorBitPostion.push_back(i*8+col3);
                                errorBitPostion.push_back(i*8+col4);

//                            cout<<"CORRECTION = "<<i*8+col1<<endl;
//                            cout<<"CORRECTION = "<<i*8+col2<<endl;
                                total++;
                                if(total==errorRows.size())
                                    goto CORRECTION;
                                else
                                    goto DOWN;
                            }
                        }
                    }
                }
            }

            /* Look for Six errors in a row*/
            for(int col1=0; col1<3; col1++)
            {
                for(int col2=col1+1; col2<4; col2++)
                {
                    for(int col3=col2+1; col3<5; col3++)
                    {
                        for(int col4=col3+1; col4<6; col4++)
                        {
                            for(int col5=col4+1; col5<7; col5++)
                            {
                                for(int col6=col5+1; col6<8; col6++)
                                {
                                    for(int hamRow=0; hamRow<4; hamRow++)
                                    {
                                        hamCodeSC[hamRow] = ham[hamRow][col1] ^ ham[hamRow][col2] ^ ham[hamRow][col3] ^ ham[hamRow][col4]^ ham[hamRow][col5] ^ ham[hamRow][col6];
                                        //cout<<hamCodeSC[hamRow]<<" ";
                                    }

                                    int same=0;
                                    for(int j=0; j<4; j++)
                                    {
                                        if(fourBitsOfSC[j] == hamCodeSC[j])
                                        {
                                            same++;
                                        }
                                    }

                                    if(same==4)
                                    {
                                        errorBitPostion.push_back(i*8+col1);
                                        errorBitPostion.push_back(i*8+col2);
                                        errorBitPostion.push_back(i*8+col3);
                                        errorBitPostion.push_back(i*8+col4);
                                        errorBitPostion.push_back(i*8+col5);
                                        errorBitPostion.push_back(i*8+col6);

//                            cout<<"CORRECTION = "<<i*8+col1<<endl;
//                            cout<<"CORRECTION = "<<i*8+col2<<endl;
                                        total++;
                                        if(total==errorRows.size())
                                            goto CORRECTION;
                                        else
                                            goto DOWN;
                                    }
                                }
                            }
                        }
                    }
                }

            }

            /* Look for Eight errors in a row*/
            for(int col1=0; col1<3; col1++)
            {
                for(int col2=col1+1; col2<4; col2++)
                {
                    for(int col3=col2+1; col3<5; col3++)
                    {
                        for(int col4=col3+1; col4<6; col4++)
                        {
                            for(int col5=col4+1; col5<7; col5++)
                            {
                                for(int col6=col5+1; col6<8; col6++)
                                {
                                    for(int col7=col6+1; col7<7; col7++)
                                    {
                                        for(int col8=col7+1; col8<8; col8++)
                                        {
                                            for(int hamRow=0; hamRow<4; hamRow++)
                                            {
                                                hamCodeSC[hamRow] =   ham[hamRow][col1]
                                                                      ^ ham[hamRow][col2]
                                                                      ^ ham[hamRow][col3]
                                                                      ^ ham[hamRow][col4]
                                                                      ^ ham[hamRow][col5]
                                                                      ^ ham[hamRow][col6]
                                                                      ^ ham[hamRow][col7]
                                                                      ^ ham[hamRow][col8];
                                                //cout<<hamCodeSC[hamRow]<<" ";
                                            }

                                            int same=0;
                                            for(int j=0; j<4; j++)
                                            {
                                                if(fourBitsOfSC[j] == hamCodeSC[j])
                                                {
                                                    same++;
                                                }
                                            }

                                            if(same==4)
                                            {
                                                errorBitPostion.push_back(i*8+col1);
                                                errorBitPostion.push_back(i*8+col2);
                                                errorBitPostion.push_back(i*8+col3);
                                                errorBitPostion.push_back(i*8+col4);
                                                errorBitPostion.push_back(i*8+col5);
                                                errorBitPostion.push_back(i*8+col6);
                                                errorBitPostion.push_back(i*8+col7);
                                                errorBitPostion.push_back(i*8+col8);

//                            cout<<"CORRECTION = "<<i*8+col1<<endl;
//                            cout<<"CORRECTION = "<<i*8+col2<<endl;
                                                total++;
                                                if(total==errorRows.size())
                                                    goto CORRECTION;
                                                else
                                                    goto DOWN;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }
DOWN:
        ;
    }

    /*
        cout<<endl;

        */

    /*for(int i=0; i<4; i++)
    {
        int fg = 0;

        for(int j=0; j<pos[i].size(); j++)
        {
            fg = 1;
            box.push_back(pos[i][j]);

        }
        if (fg == 0) goto OUT;

        for(int a=0; a<pos[i].size()-1; a++) // (a, b) makes pair combination of detected column
        {

            for(int b=a+1; b<pos[i].size(); b++)
            {
                int cn=0, sn[4]= {0,0,0,0};
                for(int hamRow=0; hamRow<4; hamRow++)
                {

                    if( (ham[hamRow][box[a]]==1 && ham[hamRow][box[b]]==1) || (ham[hamRow][box[a]]==0 && ham[hamRow][box[b]]==0) )
                    {
                        sn[hamRow] = 0;
                    }
                    else sn[hamRow] = 1;

                    if(sc[i*5+hamRow] != sn[hamRow])
                    {
                        cn=0;
                        break;
                    }
                    else
                    {
                        cn++;
                    }
                }
                if(cn==4)
                {
                    errPos.push_back(i*8+box[a]);
                    errPos.push_back(i*8+box[b]);
                    goto OUT;
                }
            }
        }
    OUT:

        box.clear();

    }

    cout<<endl;*/





CORRECTION:
    /*cout<<"Detected Error bit position(s): ";
    //cout<<"Size: "<<errorBitPostion.size()<<endl;
    for(int it=0; it<errorBitPostion.size(); it++)
    {
        cout<<errorBitPostion[it]<<" ";
    }*/
    //cout<<endl;
    int ok=1;

    cout<<"Generated: ";
    for(int aa=0; aa<genErr.size(); aa++)
        cout<<genErr[aa]<<" ";
    //cout<<endl;


    cout<<"Detected: ";
    for(int aa=0; aa<errorBitPostion.size(); aa++)
        cout<<errorBitPostion[aa]<<" ";
    //cout<<endl;

    if(genErr.size() != errorBitPostion.size())
    {
        cout<<" Status: Wrong "<<endl;
        wrong++;
    }
    else
    {

        for(int i=0; i<genErr.size(); i++)
        {
            if(genErr[i] != errorBitPostion[i])
            {
                cout<<" Status: Wrong"<<endl;
                wrong++;
                ok=0;
                break;
            }
        }
        if(ok==1)
        {
            cout<<" Status: OK"<<endl;
            correct++;
        }
    }

    genErr.clear();
    errorBitPostion.clear();


}



int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //cout<<" ************ Check The Output *************"<<endl;



    /***********Enter number of data bit *********/
    cin>>k;
    row = k/8;
    //pos.clear();
    memset(Oi, 0, sizeof(Oi));
    memset(DED, 0, sizeof(DED));

    /*********** Enter data bits***************/
    for(int i=0; i<k; i++)
        cin>>x[i];

    for(int i=0, j=5*row-1; i<row; i++)
    {
        int ix = i*8;
        columnParity[5*row-1 - j--] = x[ix] ^ x[ix+1] ^ x[ix+3] ^ x[ix+4] ^ x[ix+6];
        columnParity[5*row-1 - j--] = x[ix] ^ x[ix+2] ^ x[ix+3] ^ x[ix+5] ^ x[ix+6];
        columnParity[5*row-1 - j--] = x[ix+1] ^ x[ix+2] ^ x[ix+3] ^ x[ix+7];
        columnParity[5*row-1 - j--] = x[ix+4] ^ x[ix+5] ^ x[ix+6] ^ x[ix+7];
        columnParity[5*row-1 - j--] = x[ix] ^ x[ix+1] ^ x[ix+2] ^ x[ix+3] ^ x[ix+4] ^ x[ix+5] ^ x[ix+6] ^ x[ix+7];

    }


    for(int i=0; i<k; i++)
    {
        if(x[i]==1) parity[i%8]++;
    }
    for(int i=0; i<8; i++)
    {
        if(parity[i]%2==0) parity[i]=0;
        else parity[i]=1;
    }

    /************* Print Matrix ***********/
    /*cout<<"Input Data Matrix : "<<endl<<endl;

    for(int i = 0,temp=0,j=0; i<k; i++)
    {
        if(i%8==0) cout<<" || ";
        cout<<x[i]<<" ";
        if((i+1)%8==0)
        {
            cout<<" || ";
            for(; j<temp+5; j++)
                cout<<columnParity[j]<<" ";
            temp=temp+5;
            cout<<" || ";
            cout<<endl;

        }
    }
    cout<<" || ";
    for(int i=0; i<8; i++)
        cout<<parity[i]<<" ";
    cout<<" ||            ||";

    cout<<endl<<endl;*/




    /************ Erroneous Data *********/


    /* Occur Single Error */
    cout<<"\n\n Single Error: \n\n";
    //cout<<" Generated Error in bit    Detected Error in bit    Status\n";
    //cout<<" ~~~~~~~~~~~~~~~~~~~~~~    ~~~~~~~~~~~~~~~~~~~~~    ~~~~~~\n";
    for(int bit=0; bit<32; bit++)
    {
        for(int i=0; i<k; i++)
        {
            xerror[i]=x[i];
        }
        //xerror[i]==x[i];

        if(xerror[bit]==0) xerror[bit]=1;
        else xerror[bit]=0;

        genErr.push_back(bit);
        errorDetection();
    }

    cout<<"\n\nCorrect = "<<correct<<" Wrong = "<<wrong;
    printf(" Correct percentage =  %0.2f", (double) (100*correct)/(correct+wrong) );
    cout<<" %"<<endl;
    totalCorrect += correct;
    totalWrong += wrong;
    correct=0;
    wrong=0;

    /* Occur Two Errors */
    cout<<"\n\n Double Errors: \n\n";
    //cout<<" Generated Error in bit    Detected Error in bit    Status\n";
    //cout<<" ~~~~~~~~~~~~~~~~~~~~~~    ~~~~~~~~~~~~~~~~~~~~~    ~~~~~~\n";
    for(int bit1=0; bit1<31; bit1++)
    {
        for(int bit2=bit1+1; bit2<32; bit2++)
        {
            for(int i=0; i<k; i++)
            {
                xerror[i]=x[i];
            }
            //xerror[i]==x[i];

            if(xerror[bit1]==0) xerror[bit1]=1;
            else xerror[bit1]=0;

            if(xerror[bit2]==0) xerror[bit2]=1;
            else xerror[bit2]=0;

            genErr.push_back(bit1);
            genErr.push_back(bit2);
            errorDetection();
        }

    }

    cout<<"\n\nCorrect = "<<correct<<" Wrong = "<<wrong;
    printf(" Correct percentage =  %0.2f", (double) (100*correct)/(correct+wrong) );
    cout<<" %"<<endl;
    totalCorrect += correct;
    totalWrong += wrong;
    correct=0;
    wrong=0;

    /* Occur Three Errors */
    cout<<"\n\n Three Errors: \n\n";

    for(int bit1=0; bit1<30; bit1++)
    {
        for(int bit2=bit1+1; bit2<31; bit2++)
        {
            for(int bit3=bit2+1; bit3<32; bit3++)
            {
                for(int i=0; i<k; i++)
                {
                    xerror[i]=x[i];
                }
                //xerror[i]==x[i];

                if(xerror[bit1]==0) xerror[bit1]=1;
                else xerror[bit1]=0;

                if(xerror[bit2]==0) xerror[bit2]=1;
                else xerror[bit2]=0;

                if(xerror[bit3]==0) xerror[bit3]=1;
                else xerror[bit3]=0;

                genErr.push_back(bit1);
                genErr.push_back(bit2);
                genErr.push_back(bit3);
                errorDetection();
            }
        }

    }

    cout<<"\n\nCorrect = "<<correct<<" Wrong = "<<wrong;
    printf(" Correct percentage =  %0.2f", (double) (100*correct)/(correct+wrong) );
    cout<<" %"<<endl;
    totalCorrect += correct;
    totalWrong += wrong;
    correct=0;
    wrong=0;

    /* Occur Four Errors */
    cout<<"\n\n Four Errors: \n\n";

    for(int bit1=0; bit1<29; bit1++)
    {
        for(int bit2=bit1+1; bit2<30; bit2++)
        {
            for(int bit3=bit2+1; bit3<31; bit3++)
            {
                for(int bit4=bit3+1; bit4<32; bit4++)
                {
                    for(int i=0; i<k; i++)
                    {
                        xerror[i]=x[i];
                    }
                    //xerror[i]==x[i];

                    if(xerror[bit1]==0) xerror[bit1]=1;
                    else xerror[bit1]=0;

                    if(xerror[bit2]==0) xerror[bit2]=1;
                    else xerror[bit2]=0;

                    if(xerror[bit3]==0) xerror[bit3]=1;
                    else xerror[bit3]=0;

                    if(xerror[bit4]==0) xerror[bit4]=1;
                    else xerror[bit4]=0;


                    genErr.push_back(bit1);
                    genErr.push_back(bit2);
                    genErr.push_back(bit3);
                    genErr.push_back(bit4);
                    errorDetection();
                }
            }
        }
    }

    cout<<"\n\nCorrect = "<<correct<<" Wrong = "<<wrong;
    printf(" Correct percentage =  %0.2f", (double) (100*correct)/(correct+wrong) );
    cout<<" %"<<endl;
    totalCorrect += correct;
    totalWrong += wrong;
    correct=0;
    wrong=0;

    /* Occur Four Errors */
    cout<<"\n\n Four Errors: \n\n";

    for(int bit1=0; bit1<28; bit1++)
    {
        for(int bit2=bit1+1; bit2<29; bit2++)
        {
            for(int bit3=bit2+1; bit3<30; bit3++)
            {
                for(int bit4=bit3+1; bit4<31; bit4++)
                {
                    for(int bit5=bit4+1; bit5<32; bit5++)
                    {
                        for(int i=0; i<k; i++)
                        {
                            xerror[i]=x[i];
                        }
                        //xerror[i]==x[i];

                        if(xerror[bit1]==0) xerror[bit1]=1;
                        else xerror[bit1]=0;

                        if(xerror[bit2]==0) xerror[bit2]=1;
                        else xerror[bit2]=0;

                        if(xerror[bit3]==0) xerror[bit3]=1;
                        else xerror[bit3]=0;

                        if(xerror[bit4]==0) xerror[bit4]=1;
                        else xerror[bit4]=0;

                        if(xerror[bit5]==0) xerror[bit5]=1;
                        else xerror[bit5]=0;


                        genErr.push_back(bit1);
                        genErr.push_back(bit2);
                        genErr.push_back(bit3);
                        genErr.push_back(bit4);
                        genErr.push_back(bit5);

                        errorDetection();
                    }
                }
            }
        }
    }

    cout<<"\n\nCorrect = "<<correct<<" Wrong = "<<wrong;
    printf(" Correct percentage =  %0.2f", (double) (100*correct)/(correct+wrong) );
    cout<<" %"<<endl;
    totalCorrect += correct;
    totalWrong += wrong;
    correct=0;
    wrong=0;

    cout<<endl;

    printf("\n\nTotal Correct percentage =  %0.2f", (double) (100*totalCorrect)/(totalCorrect+totalWrong) );
    cout<<" %"<<endl;
    return 0;


    /********Error data matrix***********/
    /************************************/


    //goto GenErrorBit;

    /* Error position printing and correction */
//    if(!errPos.empty())
//    {
//        cout<<"In data bit, Error positions are:  ";
//        for(int i=0; i<errPos.size(); i++)
//        {
//            cout<<errPos[i]<<"  ";
//            xCorrect[errPos[i]] = ( xerror[errPos[i]] ^ Oi[errPos[i]/8] ) ^ ( DED[errPos[i]/8] * sp[errPos[i]%8] );
//        }
//    }
//    cout<<endl<<endl;


//    cout<<"************** Original Data Matrix was: ***********\n\n";
//
//    for(int i = 0,temp=0,j=0; i<k; i++)
//    {
//        if(i%8==0) cout<<" || ";
//        cout<<x[i]<<" ";
//        if((i+1)%8==0)
//        {
//            cout<<" || ";
//            cout<<endl;
//
//        }
//    }
//
//    cout<<endl<<endl;
//
//    cout<<"*************** Corrected Data matrix is: ***************\n\n";
//    for(int i=0; i<k; i++)
//    {
//        if(i%8==0) cout<<" || ";
//        cout<<xCorrect[i]<<" ";
//        if( (i+1)%8==0) cout<<" || "<<endl;
//    }



}

