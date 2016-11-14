#include <bits/stdc++.h>
using namespace std;
vector<int>pos;
vector<int>f1;
int main()
{
    freopen("input4.txt", "r", stdin);
    freopen("output4.txt", "w", stdout);

    int k;
    /***********Enter number of data bit *********/
    cin>>k;

    int row = k/8;
    int columnParity[5*row+1];
    int xerror[256],cerror[5*row+1],xCorrect[256];
    bool rowError[row+1];
    int x[256];
    int sp[8];
    int sc[5*row+1];
    int DED[row+1];
    int Oi[row+1];
    pos.clear();
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

    int parity[8]= {0,0,0,0,0,0,0,0};
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
    cout<<"Input Data Matrix : "<<endl<<endl;

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

    cout<<endl<<endl;

    /************ Erroneous Data *********/
    cout<<endl<<"Erroneous data bits : "<<endl;

    for(int i=0; i<k; i++)
        cin>>xerror[i];

    /********Error data matrix***********/
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
    cout<<endl;

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
    cout<<"\n\nSP =   ";
    for(int i=0; i<8; i++)
    {
        cout<<sp[i]<<"   ";
    }
    cout<<endl;
    for(int i=0; i<5*row; i++)
    {
        sc[i] = columnParity[i] ^ cerror[i];
    }
    cout<<"\nSC = ";
    for(int i=0; i<5*row; i++)
    {
        if(i%5==0) cout<<"  ";
        cout<<sc[i]<<" ";
    }
    cout<<endl<<"\n\n";


    /********Double error detection**********/

    int flag4 = 0,pp[row];
    memset(pp, 0, sizeof(pp));//here pp arrary is the first 4 bit of any 1

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
        cout << "oi "<< i << "  value "<<Oi[i]<<endl;

        flag4=0;
    }

    /**************** Error Correction ******************/

    for(int i=0;i<k;i++)
    {
        xCorrect[i]=xerror[i];
    }

    for(int i=0; i<row; i++)
    {
        if(DED[i]==1)
        {
            int position[10];
            memset(position, 0, sizeof(position));

            for(int j=0,l=0; j<8; j++)
            {
                if(sp[j]==1)
                {
                    f1.push_back(j);
                }
            }

            for(int j=0;j<f1.size();j++)
            {
                position[j]=i*8+f1[j];
                pos.push_back(position[j]);
                cout<<"\n In row "<<i+1<<" position "<<pos[j]<<""<<endl;
            }

            for(int j=0; j<pos.size(); j++)
            {
                xCorrect[pos[j]] = ( xerror[pos[j]] ^ Oi[i] ) ^ ( DED[i] * sp[pos[j]%8] );

            }
            pos.clear();
            f1.clear();

        }

    }
    cout<<endl;

    cout<<"************* Original Data Matrix was: ***********\n\n";

    for(int i = 0,temp=0,j=0; i<k; i++)
    {
        if(i%8==0) cout<<" || ";
        cout<<x[i]<<" ";
        if((i+1)%8==0)
        {
            cout<<" || ";
            cout<<endl;

        }
    }

    cout<<endl<<endl;

    cout<<"*************** Corrected Data matrix was: ***************\n\n";
    for(int i=0; i<k; i++)
    {
        if(i%8==0) cout<<" || ";
        cout<<xCorrect[i]<<" ";
        if( (i+1)%8==0) cout<<" || "<<endl;
    }



    cout<<endl;
    return 0;
}
