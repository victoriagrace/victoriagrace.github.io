//Victoria Grace
//Stereo Splitter/ Multi-band Diffuser 

//This faust code takes the sum and difference of the left and right channels of a stereo signal. 
//Two separate compressors are applied to the sum and difference signals as well as make up gain sliders
// The sum and difference signals are added and subtracted to obtain an altered version of the original left and right signals
//The new left and right channels are then split by frequency by 8 band pass filters with center frequencies increasing logarithmically
//The 16 bands are mixed in different ways in the DiffuserComp.maxpat
 
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


process = sumDiff : compressor_mono(ratio1,thresh1,.002,.4),compressor_mono(ratio2,thresh2,.002,.4):*(gainS),*(gainD) :sumDiff : *(.6),*(.6) : 
(_ <: par(i,8,bandpass(2,leftLower(i),leftHigher(i)))), (_ <: par(i,8,bandpass(2,rightLower(i),rightHigher(i))));


ratio1= hslider("ratio1",5,1,20,.01);
thresh1= hslider("thresh1",-30,-100,0,1);
ratio2= hslider("ratio2",5,1,20,.01);
thresh2= hslider("thresh2",-30,-100,0,1);

gainS=hslider("gainS",1,0.1,1.9,.01);
gainD=hslider("gainD",1,0.1,1.9,.01);

