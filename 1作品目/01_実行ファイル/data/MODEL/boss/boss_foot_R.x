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
 26;
 0.00001;1.07976;-4.29805;,
 3.32165;-0.47481;-8.91455;,
 0.00001;-0.47481;-10.82676;,
 4.69752;-0.47481;-4.29805;,
 3.32165;-0.47481;0.31845;,
 0.00001;-0.47481;2.23067;,
 -3.32164;-0.47481;0.31845;,
 -4.69750;-0.47481;-4.29805;,
 -3.32164;-0.47481;-8.91455;,
 4.69752;-4.22795;-10.82676;,
 0.00001;-4.22795;-13.53105;,
 6.64329;-4.22795;-4.29805;,
 4.69752;-4.22795;2.23067;,
 0.00001;-4.22795;4.93495;,
 -4.69751;-4.22795;2.23067;,
 -6.64329;-4.22795;-4.29805;,
 -4.69751;-4.22795;-10.82676;,
 3.32165;-7.98111;-8.91455;,
 0.00001;-7.98111;-10.82676;,
 4.69752;-7.98111;-4.29805;,
 3.32165;-7.98111;0.31845;,
 0.00001;-7.98111;2.23067;,
 -3.32164;-7.98111;0.31845;,
 -4.69750;-7.98111;-4.29805;,
 -3.32164;-7.98111;-8.91455;,
 0.00001;-9.53571;-4.29805;;
 
 32;
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
 3;18,17,25;,
 3;17,19,25;,
 3;19,20,25;,
 3;20,21,25;,
 3;21,22,25;,
 3;22,23,25;,
 3;23,24,25;,
 3;24,18,25;;
 
 MeshMaterialList {
  5;
  32;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.530400;0.395200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.298400;0.000000;0.006400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.367200;0.228800;0.060000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  32;
  0.000000;1.000000;-0.000000;,
  0.000000;0.840073;-0.542474;,
  0.478373;0.799156;-0.364017;,
  0.644259;0.764808;-0.000000;,
  0.478373;0.799156;0.364016;,
  0.000000;0.840073;0.542474;,
  -0.478373;0.799157;0.364016;,
  -0.644258;0.764808;-0.000000;,
  -0.478373;0.799157;-0.364016;,
  0.000000;0.584593;-0.811327;,
  0.677846;0.515547;-0.524153;,
  1.000000;0.000001;-0.000000;,
  0.677846;0.515547;0.524153;,
  0.000000;0.584593;0.811327;,
  -0.677845;0.515548;0.524153;,
  -1.000000;0.000001;-0.000000;,
  -0.677845;0.515548;-0.524153;,
  0.000000;-0.840071;-0.542477;,
  0.478375;-0.799154;-0.364018;,
  0.644262;-0.764805;-0.000000;,
  0.478376;-0.799154;0.364018;,
  0.000000;-0.840071;0.542477;,
  -0.478375;-0.799155;0.364018;,
  -0.644261;-0.764806;-0.000000;,
  -0.478375;-0.799155;-0.364018;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.584591;-0.811328;,
  0.677847;-0.515545;-0.524153;,
  0.677847;-0.515545;0.524153;,
  0.000000;-0.584591;0.811328;,
  -0.677846;-0.515546;0.524153;,
  -0.677846;-0.515546;-0.524153;;
  32;
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
  4;26,27,18,17;,
  4;27,11,19,18;,
  4;11,28,20,19;,
  4;28,29,21,20;,
  4;29,30,22,21;,
  4;30,15,23,22;,
  4;15,31,24,23;,
  4;31,26,17,24;,
  3;17,18,25;,
  3;18,19,25;,
  3;19,20,25;,
  3;20,21,25;,
  3;21,22,25;,
  3;22,23,25;,
  3;23,24,25;,
  3;24,17,25;;
 }
}
