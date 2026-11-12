# NumWorks Ultimate

Application externe EADK pour calculatrices NumWorks compatibles. Cette première version propose un formulaire de référence STI2D (électricité, chimie, ondes/énergie, mathématiques et mécanique).

## Construire le fichier NWA

Le workflow GitHub Actions compile automatiquement l'application à chaque push et sur demande. Le fichier `app.nwa` est publié dans l'artefact `NumWorks-Ultimate-NWA` du workflow.

## Installation

Télécharger l'artefact depuis l'onglet Actions, extraire `app.nwa`, puis l'importer avec https://my.numworks.com/apps. La compatibilité dépend de la version d'Epsilon et du modèle. Les applications externes sont masquées en mode examen et peuvent être supprimées lors d'un RESET.

## Structure

- `src/main.c` : application native.
- `src/icon.png` : icône.
- `Makefile` : compilation EADK.
- `.github/workflows/build.yml` : compilation automatisée.
- `web/index.html` : compagnon web local.

Ce projet est une application externe, pas un firmware alternatif. Elle ne lit pas les PDF et ne remplace pas le système Epsilon.