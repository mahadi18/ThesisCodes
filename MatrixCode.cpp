#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    int k;
    cout<<"Enter number of data bit: ";
    cin>>k;

    int row = k/8;
    int columnParity[5*row+1];
    int xerror[256],cerror[5*row+1];
    bool rowError[row+1];
    int x[256];
    int sp[8];
    int sc[5*row+1];
    int DED[row+1];
    int Oi[row+1];
    memset(Oi, 0, sizeof(Oi));
    memset(DED, 0, sizeof(DED));

    cout<<endl<<"Enter data bits : "<<endl;
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
    cout<<endl<<endl;

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
    cout<<endl<<"Enter erroneous data bits : "<<endl;

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
        sp[i] = parity[i] ^ parityError[i];
    }
    cout<<"\n\nSP = ";
    for(int i=0; i<8; i++)
    {
        cout<<sp[i]<<" ";
    }
    cout<<endl;
    for(int i=0; i<5*row; i++)
    {
        sc[i] = columnParity[i] ^ cerror[i];
    }
    cout<<"\n\nSc = ";
    for(int i=0; i<5*row; i++)
    {
        if(i%5==0) cout<<"  ";
        cout<<sc[i]<<" ";
    }
    cout<<endl<<"\n\n";

    cout<<"Err Data: \n";
    for(int i=0; i<k; i++)
        cout<<xerror[i]<<" ";
    cout<<endl<<endl;

    /********Double error detection**********/

    int pp=0, cc=0, f=1;
    for(int i=0; i<row; i++)
    {
        int j;
        for(j=1; j<5; j++)
        {
            if(sc[f*j-1]==1)
            {
                cc = 1;
                break;
            }
        }
        if(sc[f*j-1]==1)
        {
            pp = 1;
            Oi[i] = 1;
        }
        else Oi[i] = 0;

        if(cc=1 && pp==0) DED[i] = 1;
        else if(cc==1 && pp==1) DED[i] = 0;
        else DED[i]=0;
        f++;
        pp=0;
        cc=0;
    }

    cout<<"Err Data: \n";
    for(int i=0; i<k; i++)
        cout<<xerror[i]<<" ";
    cout<<endl<<endl;


    /**************** Error Correction ******************/









    for(int i=0; i<k; i++)
    {
        xerror[i] = ( xerror[i] ^ Oi[i%5] ) ^ ( DED[i%5] * sp[i%8] );
    }

    /* Print Corrected data */

    cout<<"||*************** So, Original Data ***************||  \n";
    for(int i=0; i<k; i++)
    {
        if(i%8==0) cout<<" || ";
        cout<<xerror[i]<<" ";
        if( (i+1)%8==0) cout<<" || "<<endl;
    }



    cout<<endl;
    return 0;
}
