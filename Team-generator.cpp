//TP 2018/2019: Zadaća 3, Zadatak 6
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <memory>

typedef std::vector<std::set<std::string>> Timovi;

struct Dijete
{
    std::string ime;
    std::shared_ptr<Dijete> sljedeci{};
};

int DajDuzinu(std::string s)
{
    int velicina=0;
    auto it=s.begin();
    while(it!=s.end())
    {
        if(((*it)>='A' && (*it)<='Z') || ((*it)>='a' && (*it)<='z') ||((*it)>='0' && (*it)<='9'))
        velicina++;
        it++;
    }
    return velicina;
}

Timovi Razvrstavanje(std::vector<std::string> v,int tim)
{
    if(v.size()<tim)
    {
        throw std::logic_error("Razvrstavanje nemoguce");
    }
    Timovi rez(tim);
    std::shared_ptr<Dijete> pocetak,prethodni;
    for(auto it=v.begin();it!=v.end();it++)
    {
        auto novi=std::make_shared<Dijete>();
        novi->ime=*it;
        std::cout<<"ime: "<<*it<<std::endl;
        if(!pocetak)
        pocetak=novi;
        else prethodni->sljedeci=novi;
        prethodni=novi;
    }
    prethodni->sljedeci=pocetak;
    int granica=tim;
    int j=v.size()/tim;
    int pom=j;
    if(v.size()%tim!=0)
    {
        if(v.size()%tim==1)
        {
            j++;
        }
        else 
        {
            j=2;
            int tim1=tim;
            while(tim1>0)
            {
                if((tim1%2==0)&& (2*tim1<v.size()))
                break;
                tim1--;
            }
        
            while((tim1+(v.size()-2*tim1))!=tim)
            {
                tim1--;
            }
            pom=j;
            granica=tim1;
        }
    }
    int i=0;
    int duzina=0;
    while(i<tim)
    {
        while(j>0)
        {
            // while(duzina>0)
            // {
            //     pocetak=pocetak->sljedeci;
            //     prethodni=prethodni->sljedeci;
            //     duzina--;
            // }
            // duzina=DajDuzinu(pocetak->ime);
            // duzina--;
            std::cout<<"Ime: "<<pocetak->ime<<std::endl;
            rez[i].insert(pocetak->ime);
            prethodni->sljedeci=pocetak->sljedeci;
            auto brisati=pocetak;
            pocetak=prethodni->sljedeci;
            j--;            
        }
        if(i<(granica-1))
        j=pom;
        else
        j=1;
        i++;
    }
    pocetak->sljedeci=nullptr;
    prethodni->sljedeci=nullptr;
    pocetak=nullptr;
    prethodni=nullptr;
    //delete prethodni;
    //delete pocetak;
    //pocetak=nullptr;
    //prethodni=nullptr;
    return rez;
}
int main ()
{
    std::cout<<"Unesite broj djece: ";
    int n;
    std::cin>>n;
    std::cin.ignore(1000,'\n');
    std::cout<<"Unesite imena djece: ";
    std::vector<std::string> v;
    std::string pomocni;
    for(int i=0;i<n;i++)
    {
        std::getline(std::cin,pomocni);
        v.push_back(pomocni);
    }
    std::cout<<"\nUnesite broj timova: ";
    int tim;
    std::cin>>tim;
    try
    {
        auto rez=Razvrstavanje(v,tim);
        for(int i=0;i<rez.size();i++)
        {
            std::cout<<"Tim "<<i+1<<":";
            auto pom=rez[i].size();
            for(auto it=rez[i].begin();it!=rez[i].end();it++)
            {
                pom--;
                std::cout<<" "<<*it;
                if(pom>0)
                std::cout<<",";
            }
            std::cout<<std::endl;
        }
    }
    catch(std::logic_error greska)
    {
        std::cout<<"Izuzetak: "<<greska.what();
    }
	return 0;
}