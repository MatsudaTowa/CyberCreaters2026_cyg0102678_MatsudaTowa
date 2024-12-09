xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 82;
 0.08900;19.80400;0.00000;,
 2.79498;19.04280;-2.70598;,
 0.08900;19.04280;-3.82683;,
 3.91583;19.04280;0.00000;,
 2.79498;19.04280;2.70598;,
 0.08900;19.04280;3.82683;,
 -2.61698;19.04280;2.70598;,
 -3.73783;19.04280;-0.00000;,
 -2.61698;19.04280;-2.70598;,
 5.08900;16.87507;-5.00000;,
 0.08900;16.87507;-7.07107;,
 7.16007;16.87507;0.00000;,
 5.08900;16.87507;5.00000;,
 0.08900;16.87507;7.07107;,
 -4.91100;16.87507;5.00000;,
 -6.98207;16.87507;-0.00000;,
 -4.91100;16.87507;-5.00000;,
 6.62181;13.63084;-6.53281;,
 0.08900;13.63084;-9.23879;,
 9.32779;13.63084;0.00000;,
 6.62181;13.63084;6.53281;,
 0.08900;13.63084;9.23879;,
 -6.44382;13.63084;6.53281;,
 -9.14979;13.63084;-0.00000;,
 -6.44382;13.63084;-6.53281;,
 7.16007;9.80400;-7.07107;,
 0.08900;9.80400;-10.00000;,
 10.08900;9.80400;0.00000;,
 7.16007;9.80400;7.07107;,
 0.08900;9.80400;10.00000;,
 -6.98207;9.80400;7.07107;,
 -9.91100;9.80400;-0.00000;,
 -6.98207;9.80400;-7.07107;,
 6.62181;5.97716;-6.53281;,
 0.08900;5.97716;-9.23879;,
 9.32779;5.97716;0.00000;,
 6.62181;5.97716;6.53281;,
 0.08900;5.97716;9.23879;,
 -6.44382;5.97716;6.53281;,
 -9.14979;5.97716;-0.00000;,
 -6.44382;5.97716;-6.53281;,
 5.08900;2.73293;-5.00000;,
 0.08900;2.73293;-7.07107;,
 7.16007;2.73293;0.00000;,
 5.08900;2.73293;5.00000;,
 0.08900;2.73293;7.07107;,
 -4.91100;2.73293;5.00000;,
 -6.98207;2.73293;-0.00000;,
 -4.91100;2.73293;-5.00000;,
 2.79498;0.56521;-2.70598;,
 0.08900;0.56521;-3.82683;,
 3.91583;0.56521;0.00000;,
 2.79498;0.56521;2.70598;,
 0.08900;0.56521;3.82683;,
 -2.61698;0.56521;2.70598;,
 -3.73783;0.56521;-0.00000;,
 -2.61698;0.56521;-2.70598;,
 0.08900;-0.19600;-0.00000;,
 16.00194;10.95313;0.00000;,
 16.36342;11.23865;-0.44416;,
 12.54371;5.34733;-1.11709;,
 12.60663;5.71641;-0.59815;,
 16.80463;11.37099;0.00000;,
 12.56051;4.82510;-0.74769;,
 16.44315;11.08548;0.44416;,
 12.62343;5.19416;-0.22876;,
 9.34663;11.48884;0.22877;,
 9.76479;11.17552;0.59816;,
 9.00821;11.64900;0.74770;,
 9.42637;11.33567;1.11709;,
 -10.07287;10.95313;0.00000;,
 -9.71139;11.23865;-0.44416;,
 -13.53111;5.34733;-1.11709;,
 -13.46818;5.71641;-0.59815;,
 -9.27018;11.37099;0.00000;,
 -13.51431;4.82510;-0.74769;,
 -9.63166;11.08548;0.44416;,
 -13.45138;5.19416;-0.22876;,
 -16.72818;11.48884;0.22877;,
 -16.31001;11.17552;0.59816;,
 -17.06660;11.64900;0.74770;,
 -16.64844;11.33567;1.11709;;
 
 88;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 3;50,49,57;,
 3;49,51,57;,
 3;51,52,57;,
 3;52,53,57;,
 3;53,54,57;,
 3;54,55,57;,
 3;55,56,57;,
 3;56,50,57;,
 4;58,59,60,61;,
 4;59,62,63,60;,
 4;62,64,65,63;,
 4;64,58,61,65;,
 4;61,60,66,67;,
 4;60,63,68,66;,
 4;63,65,69,68;,
 4;65,61,67,69;,
 4;67,66,59,58;,
 4;66,68,62,59;,
 4;68,69,64,62;,
 4;69,67,58,64;,
 4;70,71,72,73;,
 4;71,74,75,72;,
 4;74,76,77,75;,
 4;76,70,73,77;,
 4;73,72,78,79;,
 4;72,75,80,78;,
 4;75,77,81,80;,
 4;77,73,79,81;,
 4;79,78,71,70;,
 4;78,80,74,71;,
 4;80,81,76,74;,
 4;81,79,70,76;;
 
 MeshMaterialList {
  1;
  88;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  94;
  -0.000000;1.000000;0.000000;,
  -0.000000;0.924735;-0.380611;,
  0.269133;0.924735;-0.269133;,
  0.380611;0.924735;0.000000;,
  0.269133;0.924735;0.269133;,
  -0.000000;0.924735;0.380611;,
  -0.269133;0.924735;0.269133;,
  -0.380611;0.924735;0.000000;,
  -0.269133;0.924735;-0.269133;,
  -0.000000;0.709230;-0.704977;,
  0.498494;0.709230;-0.498494;,
  0.704977;0.709230;0.000000;,
  0.498494;0.709230;0.498494;,
  -0.000000;0.709230;0.704977;,
  -0.498494;0.709230;0.498494;,
  -0.704977;0.709230;0.000000;,
  -0.498494;0.709230;-0.498494;,
  -0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  -0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;-0.000000;,
  -0.652733;0.384551;-0.652733;,
  -0.000000;-0.000000;-1.000000;,
  0.707107;-0.000000;-0.707107;,
  1.000000;-0.000000;0.000000;,
  0.707107;-0.000000;0.707107;,
  -0.000000;-0.000000;1.000000;,
  -0.707107;-0.000000;0.707107;,
  -1.000000;-0.000000;0.000000;,
  -0.707107;-0.000000;-0.707107;,
  -0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;0.000000;,
  0.652733;-0.384551;0.652733;,
  -0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384551;0.000000;,
  -0.652733;-0.384551;-0.652733;,
  -0.000000;-0.709230;-0.704977;,
  0.498494;-0.709230;-0.498494;,
  0.704977;-0.709230;0.000000;,
  0.498494;-0.709230;0.498494;,
  -0.000000;-0.709230;0.704977;,
  -0.498494;-0.709230;0.498494;,
  -0.704977;-0.709230;-0.000000;,
  -0.498494;-0.709230;-0.498494;,
  -0.000000;-0.924735;-0.380611;,
  0.269133;-0.924735;-0.269133;,
  0.380611;-0.924735;0.000000;,
  0.269132;-0.924735;0.269133;,
  -0.000000;-0.924735;0.380611;,
  -0.269133;-0.924735;0.269132;,
  -0.380611;-0.924735;-0.000000;,
  -0.269133;-0.924735;-0.269132;,
  0.000000;-1.000000;-0.000000;,
  -0.836044;0.523187;0.165247;,
  -0.436592;0.838685;-0.325569;,
  0.836044;-0.523186;-0.165248;,
  0.436594;-0.838687;0.325562;,
  -0.905583;0.115343;-0.408187;,
  0.905583;-0.115345;0.408185;,
  0.887011;0.461749;0.000001;,
  0.424936;0.807965;-0.408193;,
  -0.887011;-0.461748;-0.000004;,
  -0.424940;-0.807967;0.408185;,
  0.348487;-0.669434;-0.656060;,
  0.817477;0.053905;-0.573433;,
  -0.348485;0.669433;0.656062;,
  -0.817480;-0.053905;0.573430;,
  -0.513042;-0.638714;-0.573438;,
  0.513042;0.638712;0.573441;,
  -0.050967;-0.984934;-0.165250;,
  0.050968;0.984934;0.165248;,
  -0.836044;0.523187;0.165248;,
  -0.436592;0.838685;-0.325568;,
  0.836044;-0.523186;-0.165249;,
  0.436594;-0.838687;0.325561;,
  -0.905583;0.115343;-0.408186;,
  0.905583;-0.115345;0.408184;,
  0.887011;0.461748;0.000001;,
  0.424936;0.807965;-0.408194;,
  -0.887011;-0.461748;-0.000004;,
  -0.424939;-0.807967;0.408186;,
  0.348487;-0.669434;-0.656060;,
  0.817477;0.053904;-0.573433;,
  -0.348485;0.669433;0.656063;,
  -0.817479;-0.053905;0.573431;,
  -0.513042;-0.638714;-0.573439;,
  0.513042;0.638712;0.573441;,
  -0.050967;-0.984934;-0.165250;,
  0.050968;0.984934;0.165248;;
  88;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  4;58,59,62,58;,
  4;68,60,60,69;,
  4;60,61,63,60;,
  4;70,58,58,71;,
  4;64,69,65,64;,
  4;62,66,66,72;,
  4;66,71,67,66;,
  4;63,64,64,73;,
  4;74,72,68,74;,
  4;65,75,75,59;,
  4;75,73,70,75;,
  4;67,74,74,61;,
  4;76,77,80,76;,
  4;86,78,78,87;,
  4;78,79,81,78;,
  4;88,76,76,89;,
  4;82,87,83,82;,
  4;80,84,84,90;,
  4;84,89,85,84;,
  4;81,82,82,91;,
  4;92,90,86,92;,
  4;83,93,93,77;,
  4;93,91,88,93;,
  4;85,92,92,79;;
 }
}
