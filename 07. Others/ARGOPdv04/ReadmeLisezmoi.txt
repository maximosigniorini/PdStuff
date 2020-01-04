44 ARGOPdv04 modules

ARGO is made of real-time sound and visual synthesis modules.
A module is a Pure Data patch.

ARGOPd is under a "Creative Commons" license

Documentation:
http://perso.orange.fr/Paresys/ARGOPd/

A ARGOGeneralv04.pd module (and only one) must be open before the opening of another module.

Compatibilities
All modules:
  - Work under Pd-0.38.4-extended under MacOSX.2 mini
  - Work under Pd-0.38.4-extended under WindowsXP
  - Work under Pd 0.39.2-extended-rc3 under MacOSX.4 mini
  - Work under Pd 0.39.2-extended-rc3 under WindowsXP

Except ARGOHidv04.pd
  - Does not work under WindowsXP

Except ARGO2Freeverbv04.pd
  - Does not work under Pd-0.39.2-extended-rc3 under MacOSX
    Solution: replace the file
    freeverb~.pd_darwin from Pd-0.39.2-extended-rc3
    by that one from Pd-0.38.4-extended
  - Does not work under Pd-0.39.2-extended-rc3 under Windows
    Solution: replace the file
    freeverb~.dll from Pd-0.39.2-extended-rc3
    by that one from Pd-0.38.4-extended

Except ARGOGEMVideov04.pd
  - Does not work under Pd-0.38.4-extended under MacOSX.3 + QuickTime6

Except Pd 0.39.2-extended-rc3 under WindowsXP
    If the objects: l2s stripdir gcanvas freeverb~ are not recognized:
        Move l2s.dll, stripdir.dll, gcanvas.dll, freeverb~.dll 
        in C:/Program Files/pd/extra/

(ARGO uses the libraries: creb, cyclone, freeverb, Gem, ggee, hid, iemlib, zexy, ...)

Developed under:
  - Pd-0.38.4-extended under MacOSX.3.9 + QuickTime6 (PowerBook G4)
  - Pd 0.39.2-extended-rc3 under MacOSX.4.9 + QuickTime7 (PowerBook G4)
  - Pd 0.39.2-extended-rc3 under MacOSX.4.9 + QuickTime7 (MacIntel mini)
  - Pd 0.39.2-extended-rc3 under WindowsXPpro (MacIntel mini + BootCamp)
  - Pd 0.39.2-extended-rc4 under Linux Ubuntu-Studio 7.04 Feisty Fawn

Under Pd 0.39.2-extended-rc4 under Linux Ubuntu-Studio
  - Most of the modules work except modules ARGOGEMxxx and ARGOHid
_________________________________________________________________________
_________________________________________________________________________
_________________________________________________________________________
_________________________________________________________________________
44 modules ARGOPdv04

ARGOPd est constitué de modules de synthèse et de traitement sonore
et visuel fonctionnant en temps réel sous Pure Data.

ARGOPd est sous licence libre "Creative Commons"

Documentation:
http://perso.orange.fr/Paresys/ARGOPd/

Un module ARGOGeneralv04.pd (et un seul) doit etre ouvert
avant l'ouverture d'un autre module.

Compatibilites

Tous les modules:
  - Fonctionnent sous Pd-0.38.4-extended sous MacOSX.2 mini
  - Fonctionnent sous Pd-0.38.4-extended sous WindowsXP
  - Fonctionnent sous Pd 0.39.2-extended-rc3 sous MacOSX.4 mini
  - Fonctionnent sous Pd 0.39.2-extended-rc3 sous WindowsXP

Sauf ARGOHidv04.pd
  - Ne fonctionne pas sous Windows

Sauf ARGO2Freeverbv04.pd
  - Ne fonctionne pas sous Pd-0.39.2-extended-rc3 sous MacOSX
    Solution: remplacer le fichier
    freeverb~.pd_darwin de Pd-0.39.2-extended-rc3
    par celui de Pd-0.38.4-extended
  - Ne fonctionne pas sous Pd-0.39.2-extended-rc3 sous Windows
    Solution: remplacer le fichier
    freeverb~.dll de Pd-0.39.2-extended-rc3
    par celui de Pd-0.38.4-extended

Sauf ARGOGEMVideov04.pd
  - Ne fonctionne pas sous Pd-0.38.4-extended sous MacOSX.3 + QuickTime6

Sous Pd 0.39.2-extended-rc3 sous WindowsXP
    Si les objets l2s stripdir gcanvas freeverb~ ne sont pas reconnus:
        Deplacer l2s.dll, stripdir.dll, gcanvas.dll, freeverb~.dll 
        dans C:/Program Files/pd/extra/

(ARGO utilise les libraries: creb, cyclone, freeverb, Gem, ggee, hid, iemlib, zexy, ...)

Mis au point sous:
  - Pd-0.38.4-extended sous MacOSX.3.9 + QuickTime6 (PowerBook G4)
  - Pd 0.39.2-extended-rc3 sous MacOSX.4.9 + QuickTime7 (PowerBook G4)
  - Pd 0.39.2-extended-rc3 sous MacOSX.4.9 + QuickTime7 (MacIntel mini)
  - Pd 0.39.2-extended-rc3 sous WindowsXPpro (MacIntel mini + BootCamp)
  - Pd 0.39.2-extended-rc4 sous Linux Ubuntu-Studio 7.04 Feisty Fawn

Sous Pd 0.39.2-extended-rc4 sous Linux Ubuntu-Studio
  - La plupart des modules fonctionne sauf les modules ARGOGEMxxx and ARGOHid
_________________________________________________________________________

paresys@ens.fr

File "ReadmeLisezmoi.txt" Fichier