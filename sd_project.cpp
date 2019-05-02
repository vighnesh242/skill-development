#include <cstdlib>
#include<iostream>
#include<string>
#include <hash.h>

using namespace std;

hash::hash()
{
    for(int i=0;i< tablesize;i++)
    {
        Hashtable[i]= new item;
        Hashtable[i]->name = "empty";
        Hashtable[i]->drink = "empty";
        Hashtable[i]->next = NULL;
    }
}
  void hash::AddItem(string name, string drink)
  {
      int index =Hash(name);

      if(Hashtable[index]->name == "empty")
      {
          Hashtable[index]->name = name;
          Hashtable[index]->drink = drink;
    }

    else
    {
        item* ptr = Hashtable[index];
        item* n = new item;
        n->name = name;
        n->drink = drink;
        n->next = NULL;
        while(ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = n;
    }
  }

int hash::NumberofItemsinIndex(int index)
{
	int count=0;

	if(Hashtable[index]->name=="empty")
	{
		return count;
	}
	else
	{
		count++;
		item* ptr=Hashtable[index];
		while(ptr->next!=NULL)
		{
			count++;
			ptr=ptr->next;
		}
	}
	return count;
}

void hash::PrintTable()
{
	int number;
	for(int i=0;i< tablesize; i++)
	{
		number=NumberofItemsinIndex(i);
		cout<<"-------------------\n";
		cout<<"index="<<i<<endl;
		cout<<Hashtable[i]->name<<endl;
		cout<<Hashtable[i]->drink<<endl;
		cout<<"# of items="<<number<<endl;
		cout<<"-------------------\n";


	}
}

void hash::PrintItemsInIndex(int index)
{
	item* ptr= Hashtable[index];

	if(ptr->name=="empty")
	{
		cout<<"index = "<<index<<" is empty";
	}
	else
	{
		cout<<"index "<<index<<" contains the following items\n";

		while(ptr!=NULL)
		{
			cout<<"-------------------\n";
			cout<<ptr->name<<endl;
			cout<<ptr->drink<<endl;
			cout<<"-------------------\n";
			ptr=ptr->next;
		}

	}
}

 int hash::Hash(string key)
{
   int hash = 0;
   int index;


   for(int i=0; i< key.length(); i++)
   {
       //hash= hash + (int)key[i];
       hash = (hash + (int)key[i]) * 17 ;
       //cout<<"hash="<<hash<<endl;
   }

    index=hash  % tablesize;
   return index;

}

void hash::RemoveItem(string name)
{
	int index = Hash(name);

	item* delptr;
	item* P1;
	item* P2;

	//Case 0-bucket is empty
	if(Hashtable[index]->name == "empty" && Hashtable[index]->drink == "empty")
	{
		cout<<name<< "was not found in the Hash Table\n";
	}

	//Case 1-only 1 item contained in bucket and that item has matching name
	else if(Hashtable[index]->name == name && Hashtable[index]->next == NULL)
	{
		Hashtable[index]->name = "empty";
		Hashtable[index]->drink = "empty";

		cout<< name << "was removed from the Hash Table\n";
	}

	//Case 2-match is located in the first item in the bucket but there are more items in the bucket
	else if(Hashtable[index]->name == name)
	{
		delptr = Hashtable[index];
		Hashtable[index]=Hashtable[index]->next;
		delete delptr;

		cout<< name << "was removed from the Hash Table\n";
	}

	//Case 3-bucket contains items but first item is not a match
	else
	{
		P1 = Hashtable[index]->next;
		P2 = Hashtable[index];

		while(P1!=NULL && P1->name!=name)
		{
			P2=P1;
			P1=P1->next;
		}
	}
		//Case 3.1-no match
		if(P1==NULL)
		{
			cout<<name<< "was not found in the Hash Table\n";
		}
		//Case 3.2-match is found
		else
		{
			delptr=P1;
			P1=P1->next;
			P2->next=P1;

			delete delptr;
			cout<< name << "was removed from the Hash Table\n";
		}
}


void hash::FindDrink(string name)
{
	int index = Hash(name);
	bool foundName = false;
	string drink;

	item* ptr = Hashtable[index];
	while(ptr!=NULL)
	{
		if(ptr->name == name)
		{
			foundName= true;
			drink = ptr->drink;
		}
		ptr=ptr->next;
	}
	if(foundName==true)
	{
		cout<<"Favorite drink = "<<drink<<endl;
	}
	else
	{
		cout<<name<<"'s info was not found in the Hash Table\n";
	}

}
int main(int argc, char** argv)
{
    int index;
    hash hashobj;

    index= hashobj.Hash("Aryan");
    cout<<"index="<<index<<endl;
    hash Hashy;
    string name = "";


    Hashy.AddItem("Paul","Locha");
    Hashy.AddItem("Kin","Iced Mocha");
    Hashy.AddItem("Emma","Strawberry Mocha");
    Hashy.AddItem("Annie","Hot Chocolate");
    Hashy.AddItem("Sarah","Passion Tea");
    Hashy.AddItem("Pepper","Caramel Mocha");
    Hashy.AddItem("Mike","Chai Tea");
    Hashy.AddItem("Steve","Apple");
    Hashy.AddItem("Bill","Root Beer");
    Hashy.AddItem("Marie","Skinny Latte");
    Hashy.AddItem("Susan","Water");
    Hashy.AddItem("Joe","Green Tea");

    Hashy.PrintTable();

	//Hashy.PrintItemsInIndex(0);

	while(name!="exit")
	{
		cout<<"Search for ";
		cin>>name;
		if(name!="exit")
		{
			Hashy.FindDrink(name);
		}

		cout<<"Remove ";
		cin>>name;
		if(name!="exit")
		{
			Hashy.RemoveItem(name);
		}

	}

	Hashy.PrintTable();

    Hashy.PrintItemsInIndex(0);


    return 0;

}

