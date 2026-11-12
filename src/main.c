#include <eadk.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "Atlas STI2D";
const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

#define BG       ((eadk_color_t)0x0862)
#define BAR      ((eadk_color_t)0x10A4)
#define CARD     ((eadk_color_t)0x1948)
#define ACCENT   ((eadk_color_t)0x9DFF)
#define CYAN     ((eadk_color_t)0x6F7D)
#define WHITE    ((eadk_color_t)0xFFFF)
#define MUTED    ((eadk_color_t)0xBDF7)
#define BLACK    ((eadk_color_t)0x0000)
#define ROWS     5

typedef struct {
  const char *category, *title, *formula, *unit, *hint1, *hint2;
} Entry;

static const char *categories[] = {
  "Mathematiques", "Physique", "Chimie", "2I2D - Tronc commun",
  "SIN - Numerique", "EE - Energie", "ITEC - Eco-conception",
  "AC - Construction", "Methodes & conversions"
};
#define CATEGORY_COUNT (sizeof(categories)/sizeof(categories[0]))

static const Entry entries[] = {
 {"Mathematiques","Derivee puissance","(x^n)' = n*x^(n-1)","n entier","Exemple : (x^3)' = 3x^2",""},
 {"Mathematiques","Derivee somme","(u+v)' = u' + v'","","La derivee est lineaire",""},
 {"Mathematiques","Derivee produit","(u*v)' = u'v + uv'","","Ne pas oublier les deux termes",""},
 {"Mathematiques","Derivee quotient","(u/v)' = (u'v-uv')/v^2","","Avec v different de 0",""},
 {"Mathematiques","Derivee composee","(f(u))' = u' * f'(u)","","Regle de la chaine",""},
 {"Mathematiques","Tangente","y = f'(a)(x-a)+f(a)","","Coefficient directeur : f'(a)",""},
 {"Mathematiques","Discriminant","Delta = b^2 - 4ac","","Pour ax^2+bx+c, a non nul",""},
 {"Mathematiques","Racines delta positif","x = (-b +/- sqrt(Delta))/(2a)","","Deux racines reelles distinctes",""},
 {"Mathematiques","Sommet parabole","alpha = -b/(2a)","","beta = f(alpha)",""},
 {"Mathematiques","Suite arithmetique","u(n)=u(0)+n*r","","Raison r : difference constante",""},
 {"Mathematiques","Suite geometrique","u(n)=u(0)*q^n","","Raison q : quotient constant",""},
 {"Mathematiques","Somme arithmetique","S = nombre*(premier+dernier)/2","","Nombre de termes inclus",""},
 {"Mathematiques","Somme geometrique","S = u0*(1-q^(n+1))/(1-q)","","Si q different de 1",""},
 {"Mathematiques","Pourcentage evolution","t = (Vf-Vi)/Vi","","Multiplier t par 100 pour %",""},
 {"Mathematiques","Coefficient multiplicateur","CM = 1 + t","","t en ecriture decimale",""},
 {"Mathematiques","Probabilite contraire","P(non A)=1-P(A)","","Evenement contraire",""},
 {"Mathematiques","Probabilite union","P(A ou B)=P(A)+P(B)-P(A et B)","","General, meme si incompatibles",""},
 {"Mathematiques","Probabilite conditionnelle","P_A(B)=P(A et B)/P(A)","","Si P(A) non nul",""},
 {"Mathematiques","Esperance","E(X)= somme xi * P(X=xi)","","Moyenne theorique",""},
 {"Mathematiques","Ecart-type","sigma = sqrt(V(X))","","Racine de la variance",""},
 {"Mathematiques","Trigonometrie","cos(a)=adjacent/hypotenuse","","sin(a)=oppose/hypotenuse",""},
 {"Mathematiques","Pythagore","a^2+b^2=c^2","","Triangle rectangle, c hypotenuse",""},
 {"Mathematiques","Vitesse variation","taux = (f(b)-f(a))/(b-a)","","Pente de la secante",""},
 {"Physique","Loi d Ohm","U = R * I","V, ohm, A","U tension, R resistance, I courant",""},
 {"Physique","Puissance electrique","P = U * I","W","Aussi P=R*I^2 ou U^2/R",""},
 {"Physique","Energie electrique","E = P * delta_t","J si t en s","En Wh si P en W et t en h",""},
 {"Physique","Loi des mailles","Somme algebrique U = 0","V","Dans une maille fermee",""},
 {"Physique","Loi des noeuds","Somme I entrants = sortants","A","Conservation de la charge",""},
 {"Physique","Resistance serie","Req = R1 + R2 + ...","ohm","Montage en serie",""},
 {"Physique","Resistance parallele","1/Req = somme(1/Ri)","ohm","Pour deux : R1*R2/(R1+R2)",""},
 {"Physique","Charge electrique","Q = I * delta_t","C","I en A et duree en s",""},
 {"Physique","Rendement","eta = utile / recue","sans unite","En pourcentage : eta * 100",""},
 {"Physique","Frequence periode","f = 1/T","Hz, s","T en secondes",""},
 {"Physique","Onde periodique","v = lambda * f","m/s","lambda en m, f en Hz",""},
 {"Physique","Celebrite","v = d / delta_t","m/s","Distance parcourue / duree",""},
 {"Physique","Longueur onde","lambda = v / f","m","Distance parcourue pendant une periode",""},
 {"Physique","Niveau sonore","L = 10 log10(I/I0)","dB","I0 = 1e-12 W/m2",""},
 {"Physique","Decibels intensite","I2/I1 = 10^(deltaL/10)","sans unite","Variation de niveau deltaL en dB",""},
 {"Physique","Lentille mince","1/OA' - 1/OA = 1/f'","m","Distances algebriques",""},
 {"Physique","Grandissement","gamma = A'B'/AB = OA'/OA","","Signe selon orientation",""},
 {"Physique","Energie cinetique","Ec = 0.5*m*v^2","J","m en kg, v en m/s",""},
 {"Physique","Energie potentielle","Epp = m*g*h","J","g = 9.81 N/kg",""},
 {"Physique","Poids","P = m*g","N","Masse en kg",""},
 {"Physique","Puissance mecanique","P = W/delta_t","W","Travail en joules",""},
 {"Physique","Chaleur sensible","Q = m*c*deltaT","J","c en J/(kg.K)",""},
 {"Physique","Puissance thermique","P = Q/delta_t","W","Q en joules, temps en s",""},
 {"Physique","Rendement chaine","eta_global = produit(eta_i)","","Rendements successifs",""},
 {"Chimie","Quantite matiere","n = m/M","mol","m en g, M en g/mol",""},
 {"Chimie","Concentration molaire","C = n/V","mol/L","V en litres",""},
 {"Chimie","Concentration massique","Cm = m_solute/V","g/L","Masse en grammes, volume en L",""},
 {"Chimie","Dilution","Cmere*Vmere = Cfille*Vfille","","Conservation de la quantite de solute",""},
 {"Chimie","Masse volumique","rho = m/V","kg/m3 ou g/L","Verifier les unites",""},
 {"Chimie","Densite liquide","d = rho_liquide/rho_eau","","Sans unite",""},
 {"Chimie","pH","pH = -log10([H3O+])","","Concentration en mol/L",""},
 {"Chimie","Ion oxonium","[H3O+] = 10^(-pH)","mol/L","Relation inverse du pH",""},
 {"Chimie","Quantite gaz","n = V/Vm","mol","Vm volume molaire",""},
 {"Chimie","Gaz parfaits","P*V = n*R*T","Pa, m3, mol, K","T en kelvins",""},
 {"Chimie","Avancement","n_i = n_i,0 + nu_i*x","mol","nu negatif reactif, positif produit",""},
 {"Chimie","Rendement reaction","eta = x_f/x_max","","A multiplier par 100 pour %",""},
 {"Chimie","Oxydation","Reducteur = Ox + n*e-","","Perte d'electrons",""},
 {"Chimie","Reduction","Ox + n*e- = Red","","Gain d'electrons",""},
 {"Chimie","Energie combustion","E = m * PC","J","PC en J/kg, m en kg",""},
 {"Chimie","Loi de Beer-Lambert","A = k * C","sans unite","A proportionnelle a C",""},
 {"2I2D - Tronc commun","Chaine energie","Alimenter > Distribuer > Convertir > Transmettre","","Identifier chaque fonction",""},
 {"2I2D - Tronc commun","Rendement","eta = P_sortie/P_entree","","Puissances dans la meme unite",""},
 {"2I2D - Tronc commun","Bilan puissance","P_entree = P_utile + P_pertes","W","Conservation de l'energie",""},
 {"2I2D - Tronc commun","Bilan energie","E_entree = E_utile + E_perdue","J","Sur un systeme ferme",""},
 {"2I2D - Tronc commun","Cout energie","Cout = E(kWh)*prix(kWh)","euros","Energie en kWh",""},
 {"2I2D - Tronc commun","Masse volumique","rho = m/V","kg/m3","Caracteriser un materiau",""},
 {"2I2D - Tronc commun","Contrainte mecanique","sigma = F/S","Pa","Force normale sur section",""},
 {"2I2D - Tronc commun","Deformation","epsilon = deltaL/L0","","Sans unite",""},
 {"2I2D - Tronc commun","Loi de Hooke","F = k * deltaL","N","Ressort, k en N/m",""},
 {"2I2D - Tronc commun","Frequence rotation","N = 1/T","tr/s","T en secondes",""},
 {"SIN - Numerique","Loi d Ohm capteur","U = R * I","V","Mesure tension aux bornes",""},
 {"SIN - Numerique","Diviseur tension","Us = Ue*R2/(R1+R2)","V","Sortie aux bornes de R2",""},
 {"SIN - Numerique","Puissance binaire","2^n niveaux","n bits","n bits codent 2^n valeurs",""},
 {"SIN - Numerique","Taille fichier","taille = nb_octets * 8","bits","1 octet = 8 bits",""},
 {"SIN - Numerique","Debit binaire","D = taille / duree","bit/s","Taille en bits, duree en s",""},
 {"SIN - Numerique","Periode echantillonnage","Te = 1/Fe","s","Fe en Hz",""},
 {"SIN - Numerique","Nyquist-Shannon","Fe > 2 * Fmax","Hz","Pour eviter le repliement spectral",""},
 {"SIN - Numerique","Resolution CAN","q = plage/2^n","V","n bits de resolution",""},
 {"SIN - Numerique","Adresse IPv4","32 bits","4 octets","Masque reseau separe reseau/hote",""},
 {"SIN - Numerique","Temps transmission","t = taille/debit","s","Hors latence et surcharge",""},
 {"SIN - Numerique","Loi logique ET","S = A AND B","","Vrai si A et B vrais",""},
 {"SIN - Numerique","Loi logique OU","S = A OR B","","Vrai si A ou B vrai",""},
 {"SIN - Numerique","Loi logique NON","S = NOT A","","Inverse l'etat logique",""},
 {"EE - Energie","Energie electrique","E = P * t","kWh","P en kW, t en heures",""},
 {"EE - Energie","Puissance panneau","P = U * I","W","Au point de fonctionnement",""},
 {"EE - Energie","Energie thermique","Q = m*c*deltaT","J","Chauffer un fluide ou solide",""},
 {"EE - Energie","Debit massique","Dm = m/delta_t","kg/s","Masse par seconde",""},
 {"EE - Energie","Debit volumique","Dv = V/delta_t","m3/s","Volume par seconde",""},
 {"EE - Energie","Puissance hydraulique","P = rho*g*Qv*H","W","Qv debit volumique, H hauteur",""},
 {"EE - Energie","Puissance eolienne","P = 0.5*rho*S*v^3","W","Puissance du vent incidente",""},
 {"EE - Energie","COP chauffage","COP = Q_utile/W_elec","","Performance pompe a chaleur",""},
 {"EE - Energie","Resistance thermique","Rth = deltaT/P","K/W","Ecart de temperature / puissance",""},
 {"EE - Energie","Flux thermique","Phi = deltaT/Rth","W","Regime stationnaire",""},
 {"ITEC - Eco-conception","Masse volumique","rho = m/V","kg/m3","Comparer les materiaux",""},
 {"ITEC - Eco-conception","Contrainte normale","sigma = F/S","Pa","Section en m2",""},
 {"ITEC - Eco-conception","Allongement relatif","epsilon = deltaL/L0","","Deformation relative",""},
 {"ITEC - Eco-conception","Loi de Hooke","sigma = E*epsilon","Pa","Domaine elastique lineaire",""},
 {"ITEC - Eco-conception","Durete","Essai de durete","","Comparer la resistance locale",""},
 {"ITEC - Eco-conception","Cout matiere","C = masse * prix_massique","euros","Masse et prix coherents",""},
 {"AC - Construction","Surface rectangle","S = L*l","m2","Aire d'une surface plane",""},
 {"AC - Construction","Volume parallelepipede","V = L*l*h","m3","Dimensions en metres",""},
 {"AC - Construction","Pente","p = denivele / distance","","En % : p*100",""},
 {"AC - Construction","Resistance thermique","R = e/lambda","m2.K/W","Paroi plane homogene",""},
 {"AC - Construction","Transmission thermique","U = 1/R","W/(m2.K)","Plus U est faible, meilleure isolation",""},
 {"AC - Construction","Deperdition thermique","P = U*S*deltaT","W","Ecart interieur/exterieur",""},
 {"AC - Construction","Energie de chauffage","E = P*t","Wh ou J","Duree et unite adaptees",""},
 {"Methodes & conversions","Vitesse","1 m/s = 3.6 km/h","","Multiplier m/s par 3.6",""},
 {"Methodes & conversions","Energie","1 kWh = 3.6e6 J","","1 Wh = 3600 J",""},
 {"Methodes & conversions","Pression","1 bar = 100000 Pa","","1 atm environ 1.013 bar",""},
 {"Methodes & conversions","Temperature","T(K)=theta(degC)+273.15","","Temperature absolue",""},
 {"Methodes & conversions","Prefixe kilo","k = 10^3","","mega 10^6, giga 10^9",""},
 {"Methodes & conversions","Prefixe milli","m = 10^-3","","micro 10^-6, nano 10^-9",""},
 {"Methodes & conversions","Puissance","1 kW = 1000 W","","1 MW = 1e6 W",""},
 {"Methodes & conversions","Charge","1 Ah = 3600 C","","Q = I*t",""}
};
#define ENTRY_COUNT (sizeof(entries)/sizeof(entries[0]))

static void rect(uint16_t x,uint16_t y,uint16_t w,uint16_t h,eadk_color_t c) {
  eadk_display_push_rect_uniform((eadk_rect_t){x,y,w,h},c);
}
static void txt(const char *s,uint16_t x,uint16_t y,bool big,eadk_color_t fg,eadk_color_t bg) {
  eadk_display_draw_string(s,(eadk_point_t){x,y},big,fg,bg);
}
static int count_for(int cat) {
  int n=0;
  for(unsigned i=0;i<ENTRY_COUNT;i++) if(strcmp(entries[i].category,categories[cat])==0)n++;
  return n;
}
static int entry_for(int cat,int pos) {
  int n=0;
  for(unsigned i=0;i<ENTRY_COUNT;i++) if(strcmp(entries[i].category,categories[cat])==0) {
    if(n==pos)return (int)i;
    n++;
  }
  return -1;
}
static void frame(const char *section,const char *right) {
  rect(0,0,320,240,BG);
  rect(0,0,320,34,BAR);
  txt("ATLAS STI2D",10,8,true,WHITE,BAR);
  if(right)txt(right,236,11,false,CYAN,BAR);
  rect(0,35,320,2,ACCENT);
  txt(section,10,44,false,CYAN,BG);
  rect(0,218,320,22,BAR);
  txt("OK ouvrir    BACK retour",10,224,false,MUTED,BAR);
}
static void draw_home(int selected,int offset) {
  frame("MATIERES & OUTILS","01");
  txt("Fiches de reference",10,61,true,WHITE,BG);
  for(int r=0;r<ROWS;r++) {
    int i=offset+r;
    if(i>=(int)CATEGORY_COUNT)break;
    uint16_t y=(uint16_t)(91+r*24);
    eadk_color_t b=i==selected?CARD:BG;
    rect(8,y-3,304,21,b);
    if(i==selected)rect(8,y-3,3,21,ACCENT);
    txt(categories[i],17,y,false,i==selected?WHITE:MUTED,b);
    txt(">",296,y,false,CYAN,b);
  }
  txt("Fleches : naviguer",10,204,false,MUTED,BG);
}
static void draw_list(int cat,int selected,int offset) {
  frame(categories[cat],"02");
  txt("Choisis une fiche",10,62,true,WHITE,BG);
  int count=count_for(cat);
  for(int r=0;r<ROWS;r++) {
    int pos=offset+r;
    if(pos>=count)break;
    int ix=entry_for(cat,pos);
    uint16_t y=(uint16_t)(94+r*24);
    eadk_color_t b=pos==selected?CARD:BG;
    rect(8,y-3,304,21,b);
    if(pos==selected)rect(8,y-3,3,21,ACCENT);
    txt(entries[ix].title,17,y,false,pos==selected?WHITE:MUTED,b);
    txt(">",296,y,false,CYAN,b);
  }
  txt("Fiches disponibles :",10,211,false,MUTED,BG);
}
static void draw_detail(const Entry *e) {
  frame(e->category,"03");
  txt(e->title,10,64,true,WHITE,BG);
  rect(8,91,304,54,CARD);
  txt(e->formula,15,108,true,CYAN,CARD);
  txt(e->unit,12,158,false,ACCENT,BG);
  txt(e->hint1,12,179,false,WHITE,BG);
  txt(e->hint2,12,197,false,MUTED,BG);
}
static void keep_visible(int *selected,int *offset,int count) {
  if(*selected<0)*selected=0;
  if(*selected>=count)*selected=count-1;
  if(*selected<*offset)*offset=*selected;
  if(*selected>=*offset+ROWS)*offset=*selected-ROWS+1;
}
int main(void) {
  int screen=0,cat=0,selected=0,offset=0;
  eadk_keyboard_state_t previous=0;
  bool redraw=true;
  while(true) {
    eadk_keyboard_state_t keys=eadk_keyboard_scan();
    eadk_keyboard_state_t pressed=keys & ~previous;
    previous=keys;
    if(eadk_keyboard_key_down(pressed,eadk_key_on_off))return 0;
    if(eadk_keyboard_key_down(pressed,eadk_key_back)) {
      if(screen==2)screen=1;
      else if(screen==1){screen=0;selected=cat;offset=cat<ROWS?0:cat-ROWS+1;}
      redraw=true;
    } else if(eadk_keyboard_key_down(pressed,eadk_key_up)) {
      if(screen==0){selected--;if(selected<0)selected=(int)CATEGORY_COUNT-1;keep_visible(&selected,&offset,(int)CATEGORY_COUNT);}
      else if(screen==1){selected--;if(selected<0)selected=count_for(cat)-1;keep_visible(&selected,&offset,count_for(cat));}
      redraw=true;
    } else if(eadk_keyboard_key_down(pressed,eadk_key_down)) {
      if(screen==0){selected++;if(selected>=(int)CATEGORY_COUNT)selected=0;keep_visible(&selected,&offset,(int)CATEGORY_COUNT);}
      else if(screen==1){selected++;if(selected>=count_for(cat))selected=0;keep_visible(&selected,&offset,count_for(cat));}
      redraw=true;
    } else if(eadk_keyboard_key_down(pressed,eadk_key_ok)) {
      if(screen==0){cat=selected;screen=1;selected=0;offset=0;}
      else if(screen==1){screen=2;}
      redraw=true;
    } else if(eadk_keyboard_key_down(pressed,eadk_key_left) || eadk_keyboard_key_down(pressed,eadk_key_right)) {
      if(screen==2){screen=1;redraw=true;}
    }
    if(redraw) {
      eadk_display_wait_for_vblank();
      if(screen==0)draw_home(selected,offset);
      else if(screen==1)draw_list(cat,selected,offset);
      else {int ix=entry_for(cat,selected);if(ix>=0)draw_detail(&entries[ix]);}
      redraw=false;
    }
    eadk_timing_msleep(25);
  }
  return 0;
}
