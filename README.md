<p align="center">
  <img src="src/icon.png" width="88" alt="Logo Atlas">
</p>

<h1 align="center">Atlas</h1>

<p align="center">
  <strong>Le mémo de formules STI2D sur calculatrice NumWorks.</strong><br>
  Une application externe légère pour retrouver rapidement les relations essentielles du programme.
</p>

Atlas rassemble des formules classées par discipline : mathématiques, physique, chimie, 2I2D, SIN, EE, ITEC, AC et conversions. L'objectif est simple : accéder rapidement à une formule, sans parcourir de longs paragraphes de cours.

## Fonctionnalités

- Navigation par matières, chapitres et fiches.
- Formules affichées directement, avec les unités utiles lorsqu'elles sont pertinentes.
- Navigation au clavier de la NumWorks : flèches, OK et BACK.
- Interface sombre conçue pour l'écran de la calculatrice.
- Application native externe au système Epsilon.

## Installation

1. Ouvrir la dernière [Release Atlas](https://github.com/LJM191/Atlas/releases).
2. Télécharger le fichier `app.nwa`.
3. Ouvrir [my.numworks.com/apps](https://my.numworks.com/apps) et importer le fichier.

Les applications externes sont masquées en mode examen. La compatibilité dépend de la version d'Epsilon installée.

## Commandes

| Touche | Action |
|---|---|
| Haut / Bas | Déplacer la sélection |
| OK | Ouvrir une matière ou afficher une formule |
| BACK | Revenir à la liste précédente |
| ON/OFF | Quitter Atlas |

## Compilation

Le projet utilise l'EADK NumWorks et `nwlink`. GitHub Actions compile automatiquement le fichier NWA à chaque mise à jour de `main`, puis publie l'artefact.

## Contenu pédagogique

Atlas est un aide-mémoire de révision. Les formules et leur domaine d'application doivent être vérifiés avec le cours et le référentiel de la spécialité suivie ; les contenus de SIN, EE, ITEC et AC ne sont pas interchangeables.

## Sources

- [Éduscol – Programmes et ressources STI2D](https://eduscol.education.gouv.fr/5856/programmes-et-ressources-en-serie-sti2d)
- [Éduscol – Spécialité SIN](https://sti.eduscol.education.fr/formations/bac-technologique/sti2d-specialite-systemes-dinformation-et-numerique-sin)

## Licence et marque

Atlas est un projet indépendant et non affilié à NumWorks. NumWorks et Epsilon sont des marques de leurs propriétaires respectifs.
