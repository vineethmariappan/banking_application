#include<bits/stdc++.h>
using namespace std;
int customer_id=1;
int account_number=10000;
class customer{
	int cust_id;
	int acc_no;
	string cust_name;
	long long balance;
	string encrypted_pwd;
	public:
	void set_cust_id(int cust_id){
		this->cust_id=cust_id;
	}
	void set_acc_no(int acc_no){
		this->acc_no=acc_no;
	}
	void set_cust_name(string cust_name){
		this->cust_name=cust_name;
	}
	void set_balance(long long balance){
		this->balance=balance;
	}
	void set_encrypted_pwd(string encrypted_pwd){
		this->encrypted_pwd=encrypted_pwd;
	}
	int get_cust_id(){
		return cust_id;
	}
	int get_acc_no(){
		return acc_no;
	}
	string get_cust_name(){
		return cust_name;
	}
	long long get_balance(){
		return balance;
	}
	string get_encrypted_pwd(){
		return encrypted_pwd;
	}

	
};
class bank{
	vector<customer> customers;
	public:
	void read_customer_db(){
		ifstream infile;
		infile.open("bank_db.txt");
		string a;
		customer cust;
        for(int i=0;!infile.eof(); i++){
//			infile>>a;
//			cust.cust_id=stoi(a);
//			infile>>a;
//			cust.acc_no=stoi(a);
//			infile>>a;
//			cust.cust_name=a;
//			infile>>a;
//			cust.balance=stoll(a);
//			infile>>a;
//			cust.encrypted_pwd=a;
//            customers.push_back(cust);
        }
	}
	void display_customers(){
		cout<<"CustId\tAccountNo\t Name\tBalance\tEncryptedPwd\n";
		for(int i=0;i<customers.size();i++){
			cout<<customers[i].get_cust_id()<<"\t"<<customers[i].get_acc_no()<<"\t\t"<<customers[i].get_cust_name()<<"\t"<<customers[i].get_balance()<<"\t"<<customers[i].get_encrypted_pwd()<<"\n";
		}
	}
	void withdraw(int cust_idx){
		long long amount;
		cout<<"Current Balance : "<<customers[cust_idx].get_balance()<<"\n";
		cout<<"Enter Amount to with draw\n";
		cin>>amount;
		if(customers[cust_idx].get_balance()-amount<0){
			cout<<"Entered amount is greater than your account balance\n";
		}
		else if(customers[cust_idx].get_balance()-amount<1000)
			cout<<"Entered amount cant be withdrawn since your balance will become less than 1000\n";
		else{
			customers[cust_idx].set_balance(customers[cust_idx].get_balance()-amount);
			cout<<amount<<" of money has been withdrawn\n";
			cout<<"Current Balance : "<<customers[cust_idx].get_balance()<<"\n";
		}
			
	}
	void deposit(int cust_idx){
		long long amount;
		cout<<"Current Balance : "<<customers[cust_idx].get_balance()<<"\n";
		cout<<"Enter Amount to with deposit:\n";
		cin>>amount;
		customers[cust_idx].set_balance(customers[cust_idx].get_balance()+amount);
		cout<<amount<<" of money has been depositied\n";
		cout<<"Current Balance : "<<customers[cust_idx].get_balance()<<"\n";
	}
	void account_transfer(int cust_idx){
		int acc_no;
		long long amount;
		cout<<"Enter account number to transfer money: ";
		cin>>acc_no;
			for(int i=0;i<customers.size();i++){
				if(customers[i].get_acc_no()==acc_no)
					cout<<"Enter amount to transfer: ";
					cin>>amount;
					if(customers[cust_idx].get_balance()-amount<0){
						cout<<"Entered amount is greater than your account balance\n";
					}
					else if(customers[cust_idx].get_balance()-amount<1000)
						cout<<"Entered amount cant be transfered since your balance will become less than 1000\n";
					else{
						customers[i].set_balance(customers[i].get_balance()+amount);
						customers[cust_idx].set_balance(customers[cust_idx].get_balance()-amount);
						cout<<"Transaction successful\nYour Balance: "<<customers[cust_idx].get_balance()<<"\n";
						cout<<"Balance of Acc no ("<<acc_no<<") "<<customers[i].get_balance()<<"\n";
						return;
					}
			}
			cout<<"Account Number Doesnt exist\n";
		}
	int authenticate(){
		int cust_id;
		string password;
		cout<<"Enter Customer ID\n";
		cin>>cust_id;
		cout<<"Enter password\n";
		cin>>password;
		for(int i=0;i<customers.size();i++){
			if(customers[i].get_cust_id()==cust_id && decrypt_password(customers[i].get_encrypted_pwd())==password)
				return i;
			}
		return -1;
	}
	string decrypt_password(string password){
		for(int i=0;i<password.size();i++){
			if(password[i]=='0')
				password[i]='9';
			else if(password[i]=='a')
				password[i]='z';
			else if(password[i]=='A')
				password[i]='Z';
			else 
				password[i]-=1;
		}
		return password;
	}
	string encrypt_password(string password){
		for(int i=0;i<password.size();i++){
			if(password[i]=='9')
				password[i]='0';
			else if(password[i]=='z')
				password[i]='a';
			else if(password[i]=='Z')
				password[i]='A';
			else
				password[i]+=1;
		}
		return password;
	}
	bool validate_password(string password){
		int lower=0;
		int upper=0;
		int number=0;
		for(int i=0;i<password.length();i++){
			if(islower(password[i]))
				lower++;
			else if(isupper(password[i]))
				upper++;
			else if(isdigit(password[i]))
				number++;
		}
		return lower>=2 && upper>=2 && number>=2 && password.size()>=6;
	}

	void add_new_customer(){
		customer cust;
		bool password_ok=false;
		string password,retype_password,cust_name;
		cout<<"Enter your Name: ";
		cin>>cust_name;
		do{		
			
			cout<<"(PASSWORD MUST CONTAIN 2 UPPERCASE LETTERS, 2 LOWERCASE LETTERS, 2 NUMBERS WITH MINIMUM LENGTH 6)\nEnter password : ";
			cin>>password;
			cout<<"Re-type password: ";
			cin>>retype_password;
			if(retype_password!=password)
				cout<<"Your password doesnt match, please try again\n";
			else if(!validate_password(password))
				cout<<"Your password doesnt match the criteira mentioned\n";
			else{
				password=encrypt_password(password);	
				password_ok=true;
			}
		}while(!password_ok);
		
		cust.set_acc_no(account_number++);
		cust.set_balance(10000);
		cust.set_cust_id(customer_id++);
		cust.set_cust_name(cust_name);
		cust.set_encrypted_pwd(password);
		customers.push_back(cust);
	}
		void change_password(int cust_idx){
			bool password_ok=false,current_password_ok=false;
			int cust_id=customers[cust_idx].get_cust_id();
			string cur_password,password,retype_password;
			cout<<"Enter current password\n";
			cin>>cur_password;
			for(int i=0;i<customers.size();i++){
				if(customers[i].get_cust_id()==cust_id && decrypt_password(customers[i].get_encrypted_pwd())==cur_password){
					current_password_ok=true;
				}
			}
			if(!current_password_ok) {
				cout<<"password doesnt match\n";
			}
			do{			
			cout<<"(PASSWORD MUST CONTAIN 2 UPPERCASE LETTERS, 2 LOWERCASE LETTERS, 2 NUMBERS WITH MINIMUM LENGTH 6)\nEnter password : ";
			cin>>password;
			cout<<"Re-type password: ";
			cin>>retype_password;
			if(retype_password!=password)
				cout<<"Your password doesnt match, please try again\n";
			else if(!validate_password(password))
				cout<<"Your password doesnt match the criteira mentioned\n";
			else{
				password=encrypt_password(password);	
				password_ok=true;
			}
		}while(!password_ok);
		customers[cust_idx].set_encrypted_pwd(password);
		cout<<"Password successfully changed\n";
	}
};
void dash(){
	cout<<"----------------------------------------------------------------\n";
}
int main(){
	bank simple_bank;
//	simple_bank.add_new_customer();
//	simple_bank.display_customers();
cout<<"----------------------WELCOME TO BANKING APPLICATION!----------------------\n";
	while(true){
		
		cout<<"SELECT YOUR ROLE TO PROCEED\n";
		cout<<"1. ADMIN\n2. Customer\n3.Exit";
		int choice,cust_idx;
		cin>>choice;
		bool go_back=false;
		dash();
		while(true){
		go_back=false;
		switch(choice){
			case 1:
				  while(true){
				  	go_back=false;
				   cout<<"SELECT AN OPTION TO PROCEED\n";
				   cout<<"1. View Top Customer\n";
				   cout<<"2. View Customers\n";
				   cout<<"3. Go back\n";
				   cin>>choice;
					   switch(choice){
					   	case 1:
					   		break;
					   	case 2:
					   		simple_bank.display_customers();
					   		break;
					   	case 3:
					   		go_back=true;
					   		break;
					   }
				   if(go_back)
				   		break;
				  }
				  break;
			case 2:
				while(true){
					go_back=false;
				   cout<<"SELECT AN OPTION TO PROCEED\n";
				   cout<<"1. Create New Account\n";
				   cout<<"2. Login\n";
				   cout<<"3. go back\n";
				   cin>>choice;
				   
				   switch(choice){
				   		case 1:
				   				simple_bank.add_new_customer();	
				   				break;
				   		case 2:
				   				if((cust_idx=simple_bank.authenticate())==-1){
				   					cout<<"WRONG CREDENTIALS!";
				   					break;
								}
				   				cout<<"SELECT AN OPTION TO PROCEED\n";
				   			    cout<<"1. ATM Withdrawal\n";
								cout<<"2. Cash Deposit\n";
								cout<<"3. Transfer\n";
								cout<<"4. Change Password\n";
								cout<<"5. Go Back\n";
								cout<<"6. Exit Application\n";
								cin>>choice;
								switch(choice){
									case 1:
										simple_bank.withdraw(cust_idx);
										break;
									case 2:
										simple_bank.deposit(cust_idx);
										break;
									case 3:
										simple_bank.account_transfer(cust_idx);
										 break;
									case 4:
										 simple_bank.change_password(cust_idx);
										 break;
									case 5:
										go_back=true;
										break;
									case 6:
										exit(0);
								}
								if(go_back)
									break;
							case 3:
								go_back=true;
								break;
						
				   }
				   
				   	if(go_back) 
						break;
				 }
				   break;
			case 3:
				exit(0);	   
		}
		if(go_back) break;
		}
	}
	return 0;
}
