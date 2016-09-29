//Stereo Splitter/ Multi-band Diffuser 
//Victoria Grace

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

ratio1= hslider("ratio1",5,1,20,.01);
thresh1= hslider("thresh1",-30,-100,0,1);
ratio2= hslider("ratio2",5,1,20,.01);
thresh2= hslider("thresh2",-30,-100,0,1);

gainS=hslider("gainS",1,0.1,1.9,.01);
gainD=hslider("gainD",1,0.1,1.9,.01);

process = sumDiff : compressor_mono(ratio1,thresh1,.002,.4),compressor_mono(ratio2,thresh2,.002,.4):_*gainS,_*gainD :sumDiff : *(.6),*(.6) : 
(_ <: par(i,8,bandpass(2,leftLower(i),leftHigher(i)))), (_ <: par(i,8,bandpass(2,rightLower(i),rightHigher(i))));




