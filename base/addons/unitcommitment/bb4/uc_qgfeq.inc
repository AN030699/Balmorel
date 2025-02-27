* File uc_qgfeqadd.inc Created 27-07-2011
* Lars Bregnb�k.
* Unit commitment add-on to Balmorel.
* This file is included from the QGFEQ equation in Balmorel.gms.


$ontext hans til orientering, fra balmorel.gms:
* Fuel consumption rate calculated on existing units.
QGFEQ(IA,G,IS3,T)$IAGK_Y(IA,G) ..
     VGF_T(IA,G,IS3,T)
  =E=
     (VGE_T(IA,G,IS3,T)/(GDATA(G,'GDFE')*GEFFRATE(IA,G)))$(IGNOTETOH(G) AND IGE(G))
    +(GDATA(G,'GDCV')*VGH_T(IA,G,IS3,T)/(GDATA(G,'GDFE')*GEFFRATE(IA,G)))$IGH(G)
$ifi %UnitComm%==yes $include '../../base/addons/unitcommitment/uc_qgfeqadd.inc';
;

NEDENST�ENDE linier 2 og 3 KAN GIVE MENING, HVIS 'gdfe' er angivet som h�ldning frem til maxpunktet (mw) og incl. 'gducf0'.
S� er h�ldningen for stor som udtryk for marginal, derfor skal der lige tr�kke lidt marginals fra.
MEN: dette m� vel afh�ge af antagelsen omkring 'GDUCF0' hvad ang�r hvor stor enhede (mange MW) der er beregnet under? Formentlig under 'GDUCUNITSIZE'?
s� skal dette ikke p� �n eller anden m�de indg� i linierne  2-3?


$offtext

*to be checked, not sure this is correct with bypass
* Add fixed fuel use
+ (GDATA(G,'GDUCUNITSIZE')*VUCON(IY411,IA,G,IS3,T)*GDATA(G,'GDUCF0')/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G))))$IGUC(G)

* Correct for using average efficiency as marginal efficiency
  -(GDATA(G,'GDUCF0')*VGE_T(IY411,IA,G,IS3,T)/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G))))$(IGUC(G) AND IGE(G) AND IGNOTETOH(G))
  -(GDATA(G,'GDUCF0')*GDATA(G,'GDCV')*VGH_T(IY411,IA,G,IS3,T)/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G))))$(IGUC(G) AND IGH(G))

