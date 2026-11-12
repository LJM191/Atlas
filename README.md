# NumWorks Ultimate

Application externe EADK pour calculatrices NumWorks compatibles. Cette première version propose un formulaire de référence STI2D (électricité, chimie, ondes/énergie, mathématiques et mécanique).

## Construire le fichier NWA

Le workflow GitHub Actions est défini dans `.github/workflows/build.yml`. Il compile l'application à chaque push sur `main` et peut aussi être lancé manuellement depuis l'onglet **Actions**. Le fichier `app.nwa` est publié dans l'artefact `NumWorks-Ultimate-NWA` du workflow.

## Installation

Télécharger l'artefact depuis l'onglet Actions, extraire `app.nwa`, puis l'importer avec https://my.numworks.com/apps. La compatibilité dépend de la version d'Epsilon et du modèle. Les applications externes sont masquées en mode examen et peuvent être supprimées lors d'un RESET.

## Structure

- `src/main.c` : application native.
- `src/icon.png` : icône.
- `Makefile` : compilation EADK.
- `.github/workflows/build.yml` : compilation automatisée.
- `docs/INSTALLATION.md` : guide d'installation et de dépannage.

Ce projet est une application externe, pas un firmware alternatif. Elle ne lit pas les PDF et ne remplace pas le système Epsilon.