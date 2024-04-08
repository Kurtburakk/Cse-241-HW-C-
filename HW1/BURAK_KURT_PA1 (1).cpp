#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char** argv)
{
    srand(time(NULL));
if((argv[1]==NULL)||(argv[2]==NULL))
{
    cout<<"E0"<<endl;
    exit(0);
}
if((argv[1][0]=='-')&&(argv[1][1]=='r'))
{
    int check_length=strlen(argv[2]); //given digit number check

    if(check_length==1)
    {
        const int N = argv[2][0]-48;    // convert digit number
        if((N>0)&&(N<10))       // given digit number check range[1,9]
        {
            int secret_number[N];
            int choose_num,same_num=0;

            for(int i=0;i<N;++i)
            {
                if(i==0) // choose first digit (not be 0)
                {
                    choose_num = rand() % 9 + 1;
                    secret_number[i]=choose_num;
                }
                else
                {
                    do // choose another digit
                    {
                        same_num=0;
                        choose_num = rand() % 10;
                        for(int j=0;j<i;++j)
                        {
                            if(choose_num==secret_number[j]) // this checking repeated number 
                            same_num=1;
                        }
                    }while(same_num==1);           // provide each number different
                    secret_number[i]=choose_num;   // added numbers int array
                }
            }
            //for(int i=0;i<N;++i)cout<<secret_number[i];      // given show secret number
            //cout<<endl;

            // game start
            int check_number_digit,not_number=0,c_exact=0,c_misplaced=0;
            int try_number=0;
            char user_choose_num[10];
            int proposed_number[N];
            do
            {
                not_number=0;
                
                //cout<<"enter propese number: ("<<N<<" digits)"<<endl;
                cin>>user_choose_num;
                check_length=strlen(user_choose_num); // check length entered number
                if((user_choose_num[0]-45)==0)
                {
                    cout<<"E0"<<endl;
                    exit(0); 
                }
                for(int i=0;i<check_length;++i)
                {
                        check_number_digit=user_choose_num[i]-48; // convert integer
                        if(!((check_number_digit>=0)&&(check_number_digit<10)))
                        {
                            cout<<"E2"<<endl;
                            exit(0); 
                        }
                }
                if(check_length==N) 
                {
                    for(int i=0;i<N;++i)
                    {
                        check_number_digit=user_choose_num[i]-48; // convert integer

                        if((check_number_digit>=0)&&(check_number_digit<10))
                        {
                            if((i==0)&&(check_number_digit==0))  // check first digit
                            not_number=1;
                            if(not_number==0)                            
                            proposed_number[i]=check_number_digit;   // entered number check and added int array
                        }
                        else
                        not_number=1; 
                    }
                        for(int i=0;i<N;++i) //check have same digit
                        {
                            for(int j=i+1;j<N;++j)
                            if(proposed_number[i]==proposed_number[j])
                            not_number=1;
                        }
                    if(not_number==0)
                    {
                        for(int i=0;i<N;++i)
                        {
                            for(int j=0;j<N;++j)
                            {
                                if(i==j)
                                {
                                    if(proposed_number[i]==secret_number[j]) // find C_exact value
                                    ++c_exact;
                                }
                                if(i!=j)
                                {
                                    if(proposed_number[i]==secret_number[j]) // find C_misplaced value
                                    ++c_misplaced;
                                }
                            }
                        }
                        if(c_exact==N)  // if each digit equal to secret number
                        {
                            cout << "FOUND " << try_number << endl;
                            exit(0);
                        }
                        else            // if not equal each letter
                        {
                            cout << c_exact <<" " <<c_misplaced <<endl;
                        }
                        c_exact=0;
                        c_misplaced=0;
                    }
                    else
                    {
                    cout<<"E2"<<endl;
                    exit(0);
                    }
                }
                else
                {
                cout<<"E1"<<endl;
                exit(0);
                }
                ++try_number;
            }while(try_number<100);
        }
        else
        {
        cout<<"E0"<<endl;
        exit(0);
        }
            
    }
    else
    {
        cout<<"E0"<<endl;
        exit(0);
    }

}
else if((argv[1][0]=='-')&&(argv[1][1]=='u'))
{
    int check_length=strlen(argv[2]); //given digit number check

    if((check_length>0)&&(check_length<10))
    {
        const int N = check_length;
        int secret_number[N];
        int choose_num,same_num=0;
        int check_number_digit,not_number=0;
    
        for(int i=0;i<N;++i)
        {
            if((argv[2][0]-45)==0)
            {
                cout<<"E0"<<endl;
                exit(0); 
            }
            check_number_digit=argv[2][i]-48; //convert number
            if((check_number_digit>=0)&&(check_number_digit<10))
            {
                if((i==0)&&(check_number_digit==0)){ // first digit not be 0
                not_number=1;
                }
                if(not_number==0)
                secret_number[i]=check_number_digit; // convert integer array
            }
            else
            not_number=1; 
        }
        if(not_number==0) // check number
        {
            for(int i=0;i<N;++i) //check same digit
            {
                for(int j=i+1;j<N;++j)
                {
                    if(secret_number[i]==secret_number[j]) 
                    not_number=1;
                }
            }
            if(not_number==1)
            {
                cout<<"E0"<<endl;
                exit(0);
            }
        }
        else
        {
            cout<<"E0"<<endl;
            exit(0);
        }

            //for(int i=0;i<N;++i)cout<<secret_number[i]; // check secret number
            //cout<<endl;
            // game start
            
            int try_number=0;
            char user_choose_num[10];
            int proposed_number[N];  //user entered number convert int
            int c_exact=0;
            int c_misplaced=0;

            do
            {
                //cout<<"enter propese number: ("<<N<<" digits)"<<endl;
                not_number=0;
                cin>>user_choose_num;
                //cout<<user_choose_num<<endl;
                check_length=strlen(user_choose_num);  //find length of the enteren number
                if((user_choose_num[0]-45)==0)
                {
                cout<<"E0"<<endl;
                exit(0); 
                }
                for(int i=0;i<check_length;++i)
                {
                        check_number_digit=user_choose_num[i]-48; // convert integer
                        if(!((check_number_digit>=0)&&(check_number_digit<10)))
                        {
                            cout<<"E2"<<endl;
                            exit(0); 
                        }
                }
                if(check_length==N) // check length entered number equal to secret number
                {
                    for(int i=0;i<N;++i)
                    {
                        check_number_digit=user_choose_num[i]-48;

                        if((check_number_digit>=0)&&(check_number_digit<10))  // check each digit is number
                        {
                            if((i==0)&&(check_number_digit==0))  //check first element
                            not_number=1;
                            if(not_number==0)                            
                            proposed_number[i]=check_number_digit;
                        }
                        else
                        not_number=1;
                        
                    }
                    for(int i=0;i<N;++i) //check same digit
                    {
                        for(int j=i+1;j<N;++j)
                        if(proposed_number[i]==proposed_number[j])
                        {
                            cout<<"E0"<<endl;
                            exit(0);
                        }
                    }
                    if(not_number==0)
                    {
                        for(int i=0;i<N;++i)
                        {
                            for(int j=0;j<N;++j)
                            {
                                if(i==j)
                                {
                                if(proposed_number[i]==secret_number[j])   // find C_exact value
                                ++c_exact;
                                }
                                if(i!=j)
                                {
                                if(proposed_number[i]==secret_number[j])   // find C_misplaced value
                                ++c_misplaced;
                                }
                            }
                        }
                        if(c_exact==N)  // if found secret number
                        {
                            cout << "FOUND " << try_number << endl;
                            exit(0);
                        }
                        else            //if not equal to each letter
                        {
                            cout << c_exact <<" " <<c_misplaced <<endl;
                        }
                        c_exact=0; //reset 
                        c_misplaced=0;
                    }
                    else
                    {
                    cout<<"E2"<<endl;
                    exit(0);
                    }
                }
                else
                {
                cout<<"E1"<<endl;
                exit(0);
                }
                ++try_number;
            }while(try_number<100); // continue found number or try number equal to 100
    }
    else
    {
        cout<<"E0"<<endl;
        exit(0);
    }
}
else  // wrong input while compile
{
    cout<<"E0"<<endl;
    exit(0);
}

    return 0;
}