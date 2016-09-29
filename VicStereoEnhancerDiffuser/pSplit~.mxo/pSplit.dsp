// Enter Faust code here

//Phaser Stereo Splitter/ Multi-band Diffuser


//   _ : phaser2_mono(Notches,width,frqmin,fratio,frqmax,LFOspeed,depth,fb,invert) : _;


import("effect.lib");
import("filter.lib");

sumDiff(L,R)=L+R, L-R;

leftLow = (100,200,400,800,1600,3200,6400,12800);
leftLower(i) = take(i+1,leftLow);

leftHigh = (200,400,800,1600,3200,6400,12800,44100);
leftHigher(i) = take(i+1,leftHigh);

rightLow = (100,200,400,800,1600,3200,6400,12800);
rightLower(i) = take(i+1,rightLow);

rightHigh = (200,400,800,1600,3200,6400,12800,44100);
rightHigher(i) = take(i+1,rightHigh);


phaserS=phaser2_mono(1,1,widthS,frqminD,fratioS,100,LFOspeedS,1,0,0);
phaserD=phaser2_mono(1,1,widthD,frqminD,fratioD,100,LFOspeedD,1,0,0);

//sliders for difference phaser

widthS=hslider("widthS",50,0,100,1);
fratioS=hslider("ratioS",2,0.1,5,.01);
LFOspeedS= hslider("LFOspeedS",2,.01,10,.001);
frqminS= hslider("frqminS",2,.1,50,.1);
gainS=hslider("gainS",1,.1,1.9,.01);


process = sumDiff : phaserS,phaserD:_*gainS,_*gainD :sumDiff : *(.7),*(.7) : 
(_ <: par(i,8,bandpass(2,leftLower(i),leftHigher(i)))), (_ <: par(i,8,bandpass(2,rightLower(i),rightHigher(i))));

//sliders for difference phaser

widthD=hslider("widthS",50,0,100,1);
fratioD=hslider("ratioS",2,0.1,5,.01);
LFOspeedD= hslider("LFOspeedS",2,.01,10,.001);
frqminD= hslider("frqminD",2,.1,50,.1);
gainD=hslider("gainD",1,.1,1.9,.01);



