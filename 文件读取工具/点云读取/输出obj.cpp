cv::imwrite(resPath + "texture_mesh_UNMERGE.png", textureImage);

string objName_unmerge = resPath + "texture_mesh_UNMERGE.obj";
std::ofstream objOut_unmerge(objName_unmerge.c_str());
objOut_unmerge << "mtllib texture_mesh_UNMERGE.mtl" << std::endl;
objOut_unmerge << "usemtl texture_mesh_UNMERGE" << std::endl;
vertexCount = triMesh.GetVertexCount();
for (Int vid = 0; vid < vertexCount; vid++)
{
    Vector3 coord = triMesh.GetVertexCoord(vid);
    objOut_unmerge << "v " << coord[0] << " " << coord[1] << " " << coord[2] << "\n";
}
Int faceCount = triMesh.GetTriangleCount();
for (Int fid = 0; fid < faceCount; fid++)
{
    for (int localId = 0; localId < 3; localId++)
    {
        Int tid = faceTexIds.at(fid * 3 + localId);
        objOut_unmerge << "vt " << texCoords.at(tid * 2) << " " << texCoords.at(tid * 2 + 1) << "\n";
    }
}
Int vertexIds_unmerge[3];
for (Int fid = 0; fid < faceCount; fid++)
{
    triMesh.GetTrianglevertexIds_unmerge(fid, vertexIds_unmerge);
    objOut_unmerge << "f " << vertexIds_unmerge[0] + 1 << "/" << fid * 3 + 1 << " "
        << vertexIds_unmerge[1] + 1 << "/" << fid * 3 + 2 << " " << vertexIds_unmerge[2] + 1 << "/" << fid * 3 + 3 << "\n";
}
objOut_unmerge.close();

// export mtl file
string mtlName_unmerge = resPath + "texture_mesh_UNMERGE.mtl";
std::ofstream mtlOut_unmerge(mtlName_unmerge.c_str());
mtlOut_unmerge << "newmtl texture_mesh_UNMERGE" << std::endl;
mtlOut_unmerge << "Kd " << 0.75 << " " << 0.75 << " " << 0.75 << std::endl;
mtlOut_unmerge << "map_Kd texture_mesh_UNMERGE.png" << std::endl;
mtlOut_unmerge.close();