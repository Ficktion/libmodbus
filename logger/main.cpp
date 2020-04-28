#include<iostream>
#include<unistd.h>
#include <modbus/modbus.h>
#include<stdlib.h>
#include<fstream>
#include<ctime>

using namespace std;

int rejestr_koncowy;

int zwloka;
int rk;
char adres[15];

string nazwa;

int port;

modbus_t *ctx;

uint16_t tab_reg[16];

int a;

int wartosc_rejestru(){

int rc;
int i;



ctx = modbus_new_tcp(adres, port);

fstream plik;


if (modbus_connect(ctx) == -1) {
    cout<<(stderr, "Blad polaczenia: %s\n", " ", modbus_strerror(errno));
    modbus_free(ctx);

}
rc = modbus_read_registers(ctx, a, 1, tab_reg);

if (rc == -1) {
    cout<<(stderr, "%s\n", " ",modbus_strerror(errno));

}

for (i=0; i < rc; i++) {
    cout<<(tab_reg[i]);

    plik.open(nazwa,ios::out | ios::app);

       plik<<(tab_reg[i]);

    plik.close();

}
cout<<endl;

modbus_close(ctx);
modbus_free(ctx);

}

int main(void) {

fstream plik;

    rejestr_koncowy=rejestr_koncowy;
    system("clear");

    cout<<"Logger Rejestrow MODBUS TCP/IP urzadzen WALTER KOMPRESSORTECHNIK"<<endl;
    cout<<endl;

    cout<<"Podaj Adres IP urzadzenia MODBUS: ";
    cin>>adres;
    cout<<endl;

    cout<<"Podaj port urzadzenia MODBUS: ";
    cin>>port;
    cout<<endl;

    cout<<"Podaj koniec zakresu rejestrow MODBUS: ";
    cin>>rejestr_koncowy;
    cout<<endl;

    cout<<"Zapis danych co: ";
    cin>>zwloka;
    cout<<endl;

    cout<<"Nazwa Pliku loga: ";
    cin>>nazwa;
    cout<<endl;



for(a = 0;a<=rejestr_koncowy;a++){

cout<<"Rejestr "<<a<<": ";

plik.open(nazwa,ios::out | ios::app);

plik<<" Reg_"<<a<<",";

plik.close();

wartosc_rejestru();



usleep(120000);

if (a>=rejestr_koncowy){

    a=0;
    plik.open(nazwa,ios::out | ios::app);

        plik<<endl;

  time_t rawtime;
  struct tm * timeinfo;

char buffer[24];
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

   strftime (buffer,24," %F/%H-%M-%S",timeinfo);

    plik<<buffer;

plik.close();
sleep(zwloka);
}


}

  while(0);
}
