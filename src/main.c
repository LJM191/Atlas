#include <eadk.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "NU Ultimate";
const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

#define C_BG      ((eadk_color_t)0x0862)
#define C_PANEL   ((eadk_color_t)0x10A4)
#define C_PANEL2  ((eadk_color_t)0x1948)
#define C_ACCENT  ((eadk_color_t)0x9DFF)
#define C_CYAN    ((eadk_color_t)0x6F7D)
#define C_WHITE   ((eadk_color_t)0xFFFF)
#define C_MUTED   ((eadk_color_t)0xBDF7)

typedef struct {
  const char *category;
  const char *title;
  const char *formula;
  const char *line1;
  const char *line2;
} Formula;

static const Formula formulas[] = {
  {"ELECTRICITE", "Loi d'Ohm", "U = R x I", "U en volts, R en ohms,", "I en amperes."},
  {"ELECTRICITE", "Puissance", "P = U x I", "P en watts (W).", "Aussi: P = R x I^2."},
  {"ELECTRICITE", "Energie", "E = P x dt", "E en joules si dt en s.", "1 Wh = 3600 J."},
  {"ELECTRICITE", "Serie", "Req = R1 + R2", "Les resistances", "s'additionnent."},
  {"ELECTRICITE", "Parallele", "1/Req = 1/R1 + 1/R2", "Pour deux resistances:", "Req = R1*R2/(R1+R2)."},
  {"CHIMIE", "Concentration molaire", "C = n / V", "C en mol/L, n en mol,", "V en litres."},
  {"CHIMIE", "Concentration massique", "Cm = m / V", "Cm en g/L, m en g,", "V en litres."},
  {"CHIMIE", "Dilution", "C1 x V1 = C2 x V2", "La quantite de solute", "reste constante."},
  {"CHIMIE", "Quantite de matiere", "n = m / M", "m en grammes, M en", "g/mol, n en mol."},
  {"CHIMIE", "pH", "pH = -log10([H3O+])", "[H3O+] en mol/L.", "pH bas: solution acide."},
  {"ONDES / ENERGIE", "Celebrite", "v = d / dt", "Distance divisee par", "la duree."},
  {"ONDES / ENERGIE", "Onde periodique", "v = lambda x f", "lambda en metres, f en Hz,", "v en m/s."},
  {"ONDES / ENERGIE", "Periode", "T = 1 / f", "T en secondes (s).", "f en hertz (Hz)."},
  {"ONDES / ENERGIE", "Puissance thermique", "P = Q / dt", "Q en joules, dt en s.", "P en watts."},
  {"ONDES / ENERGIE", "Pouvoir calorifique", "PC = Q / m", "Q en joules, m en kg.", "PC en J/kg."},
  {"MATHEMATIQUES", "Derivee puissance", "(x^n)' = n*x^(n-1)", "Exemple: (x^3)' = 3x^2.", "n est un entier."},
  {"MATHEMATIQUES", "Suite arithmetique", "un = u0 + n*r", "r est la raison.", "Ecart constant."},
  {"MATHEMATIQUES", "Suite geometrique", "un = u0 * q^n", "q est la raison.", "Rapport constant."},
  {"MATHEMATIQUES", "Somme geometrique", "S = u0*(1-q^(n+1))/(1-q)", "Valable si q different", "de 1, de u0 a un."},
  {"MECANIQUE", "Vitesse moyenne", "v = d / dt", "d en metres, dt en s.", "v en m/s."},
  {"MECANIQUE", "Poids", "P = m x g", "m en kg, g = 9.81 N/kg.", "P en newtons (N)."}
};
#define FORMULA_COUNT (sizeof(formulas) / sizeof(formulas[0]))

static const char *categories[] = {
  "ELECTRICITE", "CHIMIE", "ONDES / ENERGIE", "MATHEMATIQUES", "MECANIQUE"
};
#define CATEGORY_COUNT (sizeof(categories) / sizeof(categories[0]))

static void fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, eadk_color_t c) {
  eadk_display_push_rect_uniform((eadk_rect_t){x,y,w,h}, c);
}
static void text(const char *s, uint16_t x, uint16_t y, bool large, eadk_color_t fg, eadk_color_t bg) {
  eadk_display_draw_string(s, (eadk_point_t){x,y}, large, fg, bg);
}
static void frame(const char *section) {
  fill(0,0,320,240,C_BG);
  fill(0,0,320,32,C_PANEL);
  text("NUMWORKS ULTIMATE", 12, 7, true, C_WHITE, C_PANEL);
  fill(0,33,320,2,C_ACCENT);
  text(section, 12, 42, false, C_CYAN, C_BG);
  fill(0,220,320,20,C_PANEL);
  text("OK: choisir    BACK: retour", 10, 226, false, C_MUTED, C_PANEL);
}
static void wait_release(void) { eadk_timing_msleep(130); }
static void draw_home(int selected) {
  frame("FORMULAIRE STI2D");
  text("Tes reperes de cours", 12, 62, true, C_WHITE, C_BG);
  for (int i=0;i<(int)CATEGORY_COUNT;i++) {
    uint16_t y = 94 + i*24;
    eadk_color_t bg = i==selected ? C_PANEL2 : C_BG;
    fill(8,y-3,304,21,bg);
    if (i==selected) fill(8,y-3,3,21,C_ACCENT);
    text(categories[i], 18, y, false, i==selected?C_WHITE:C_MUTED, bg);
    text(">", 294, y, false, C_CYAN, bg);
  }
}
static int category_count(const char *category) {
  int n=0;
  for (unsigned i=0;i<FORMULA_COUNT;i++) if (strcmp(formulas[i].category,category)==0) n++;
  return n;
}
static int formula_index(const char *category, int visible_index) {
  int n=0;
  for (unsigned i=0;i<FORMULA_COUNT;i++) if (strcmp(formulas[i].category,category)==0) {
    if (n==visible_index) return (int)i;
    n++;
  }
  return -1;
}
static void draw_list(int category, int selected) {
  frame(categories[category]);
  text("Selectionne une formule", 12, 62, true, C_WHITE, C_BG);
  int row=0;
  for (unsigned i=0;i<FORMULA_COUNT;i++) {
    if (strcmp(formulas[i].category,categories[category])!=0) continue;
    uint16_t y=94+row*22;
    eadk_color_t bg=row==selected?C_PANEL2:C_BG;
    fill(8,y-3,304,20,bg);
    if(row==selected) fill(8,y-3,3,20,C_ACCENT);
    text(formulas[i].title,18,y,false,row==selected?C_WHITE:C_MUTED,bg);
    row++;
  }
}
static void draw_detail(const Formula *f) {
  frame(f->category);
  text(f->title,12,65,true,C_WHITE,C_BG);
  fill(10,98,300,48,C_PANEL2);
  text(f->formula,18,114,true,C_CYAN,C_PANEL2);
  text(f->line1,14,165,false,C_WHITE,C_BG);
  text(f->line2,14,184,false,C_WHITE,C_BG);
  text("BACK pour revenir a la liste",14,202,false,C_MUTED,C_BG);
}
int main(void) {
  int category=0, selected=0, screen=0, current_formula=0;
  draw_home(selected);
  while (true) {
    eadk_keyboard_state_t k=eadk_keyboard_scan();
    if (eadk_keyboard_key_down(k,eadk_key_on_off)) return 0;
    if (eadk_keyboard_key_down(k,eadk_key_back)) {
      if (screen==2) screen=1; else if (screen==1) screen=0;
      wait_release();
    } else if (eadk_keyboard_key_down(k,eadk_key_up)) {
      if (selected>0) selected--;
      wait_release();
    } else if (eadk_keyboard_key_down(k,eadk_key_down)) {
      int max = screen==0 ? (int)CATEGORY_COUNT-1 : category_count(categories[category])-1;
      if (selected<max) selected++;
      wait_release();
    } else if (eadk_keyboard_key_down(k,eadk_key_ok)) {
      if (screen==0) { category=selected; selected=0; screen=1; }
      else if (screen==1) { current_formula=formula_index(categories[category],selected); if(current_formula>=0) screen=2; }
      wait_release();
    }
    if (screen==0) draw_home(selected);
    else if (screen==1) draw_list(category,selected);
    else draw_detail(&formulas[current_formula]);
    eadk_timing_msleep(35);
  }
  return 0;
}
