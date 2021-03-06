#ifndef MACHINGCUBE_H_
#define MACHINGCUBE_H_
//----------------------------------------------------------------------------------------------------------------------
/// @file MachineCube.h
/// @brief basic maching cube algorithm
//----------------------------------------------------------------------------------------------------------------------
// must include types.h first for ngl::Real and GLEW if required

#include <GL/glew.h>

#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <cmath>

//----------------------------------------------------------------------------------------------------------------------
/// @class MachingCube "include/MachingCube.h"
/// @brief basic maching cube algorithm
/// @author Xiaosong Yang, Idris Miles
/// @version 1.0
/// @date 14/01/13, 14/01/2017
//----------------------------------------------------------------------------------------------------------------------


// code from http://paulbourke.net/geometry/polygonise/

typedef struct {
   glm::vec3    p[8];
   float        val[8];
} Voxel;

typedef struct {
    glm::vec3    p[3];         /* Vertices */
} Triangle;

// code finished

class MachingCube
{
public :

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief default constructor
    //----------------------------------------------------------------------------------------------------------------------
    MachingCube();

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief default destructor
    //----------------------------------------------------------------------------------------------------------------------
    ~MachingCube();

    //----------------------------------------------------------------------------------------------------------------------
    void Polygonize(std::vector<glm::vec3> &_verts, std::vector<glm::vec3> &_norms, float *_volumeData, const float &_isolevel, const int &_w, const int &_h, const int &_d, const float &_voxelW = 1.0f, const float &_voxelH = 1.0f, const float &_voxelD = 1.0f);
    void Polygonize(std::vector<glm::vec3> &_verts, std::vector<glm::vec3> &_norms, std::string _vol, const int &_w, const int &_h, const int &_d, const float &_voxelW = 1.0f, const float &_voxelH = 1.0f, const float &_voxelD = 1.0f);

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief draw method to get the machingcube triangle vertices and normals
    //----------------------------------------------------------------------------------------------------------------------
    void GetVerts(std::vector<glm::vec3> &_verts, std::vector<glm::vec3> &_norms);
    //----------------------------------------------------------------------------------------------------------------------

protected :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief  load an volume data from a file
    /// @param[in]  &_vol Volume Data File name
    //----------------------------------------------------------------------------------------------------------------------
    bool LoadVolumeFromFile(std::string _vol, const int &_w, const int &_h, const int &_d, const float &_voxelW = 1.0f, const float &_voxelH = 1.0f, const float &_voxelD = 1.0f);

    //----------------------------------------------------------------------------------------------------------------------
    void generateVolume(float *_volumeData, const float &_isolevel, const int &_w, const int &_h, const int &_d, const float &_voxelW = 1.0f, const float &_voxelH = 1.0f, const float &_voxelD = 1.0f);

    //----------------------------------------------------------------------------------------------------------------------
    void createVerts();

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief extract triangles from each voxel, add the triangles into tri vector
    //----------------------------------------------------------------------------------------------------------------------
    unsigned int MachingTriangles(Voxel g, float iso, std::vector<Triangle> &triList);

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief intepolate the intersection point from the level value
    //----------------------------------------------------------------------------------------------------------------------
    glm::vec3 VertexInterp(float isolevel, glm::vec3 p1, glm::vec3 p2, float valp1, float valp2);

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief compute the normal from the three vertices
    //----------------------------------------------------------------------------------------------------------------------
    glm::vec3 computeTriangleNormal(Triangle &itr);


    //----------------------------------------------------------------------------------------------------------------------
    /// @brief The volume data
    //----------------------------------------------------------------------------------------------------------------------
    float           *volumeData;
    float           isolevel;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief The volume data dimension
    //----------------------------------------------------------------------------------------------------------------------
    unsigned int volume_width;
    unsigned int volume_height;
    unsigned int volume_depth;
    unsigned int volume_size;

    float voxel_width;
    float voxel_height;
    float voxel_depth;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief The number of vertices in the object
    //----------------------------------------------------------------------------------------------------------------------
    unsigned long int m_nVerts;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief array of mesh verts and norms
    std::vector <glm::vec3> m_meshVerts;
    std::vector <glm::vec3> m_meshNorms;
    //----------------------------------------------------------------------------------------------------------------------

};

#endif
//----------------------------------------------------------------------------------------------------------------------

