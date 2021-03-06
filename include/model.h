#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "include/rig.h"
#include "include/mesh.h"

#include "ScalarField/Hrbf/hrbf_core.h"
#include "ScalarField/Hrbf/hrbf_phi_funcs.h"
#include "ScalarField/fieldfunction.h"

#include "BinaryTree/interiornode.h"
#include "BinaryTree/leafnode.h"

#include "Machingcube/MachingCube.h"


enum RenderType { SKINNED = 0, RIG, ISO_SURFACE, NUMRENDERTYPES };
typedef HRBF_fit<float, 3, Rbf_pow3<float> > HRBF;

class Model
{
public:


    Model();
    ~Model();
    void Load(const std::string &_mesh);
    void DrawMesh();
    void DrawRig();
    void Animate(const float _animationTime);

    void ToggleWireframe();

    void CreateShaders();
    void DeleteShaders();

    void CreateVAOs();
    void DeleteVAOs();
    void UpdateVAOs();


    void SetLightPos(const glm::vec3 &_lightPos);
    void SetModelMatrix(const glm::mat4 &_modelMat);
    void SetNormalMatrix(const glm::mat3 &_normMat);
    void SetViewMatrix(const glm::mat4 &_viewMat);
    void SetProjectionMatrix(const glm::mat4 &_projMat);

    void UploadBoneColoursToShader(RenderType _rt);
    void UploadBonesToShader(RenderType _rt);


    //-------------------------------------------------------------------
    void UpdateImplicitSurface(int xRes = 32,
                               int yRes = 32,
                               int zRes = 32,
                               float dim = 800.0f,
                               float xScale = 800.0f,
                               float yScale = 800.0f,
                               float zScale = 800.0f);


    void GenerateMeshParts();
    void GenerateFieldFunctions();
    void GenerateGlobalFieldFunctions();
    void GenerateMeshVertIsoValue();

    void GenerateOneRingNeighbours();
    void GenerateCentroidWeights();

    //-------------------------------------------------------------------

    void PerformLBWSkinning();
    void PerformVertexProjection();
    void PerformTangentialRelaxation();
    void PerformLaplacianSmoothing();


    //-------------------------------------------------------------------
    // Attributes
    Rig m_rig;
    Mesh m_mesh;
    Mesh m_rigMesh;

    std::vector<Mesh> m_meshParts;

    std::vector<FieldFunction> m_fieldFunctions;
    std::shared_ptr<AbstractNode> m_compositionTree;
    Mesh m_meshIsoSurface;

    std::vector<float> m_meshVertIsoValues;
    std::vector<std::vector<unsigned int>> m_meshVertOneRingNeighbour;
    std::vector<std::vector<float>> m_meshVertCentroidWeights;

    MachingCube m_polygonizer;

    bool m_wireframe;
    bool m_initGL;

    glm::vec3 m_lightPos;
    glm::mat4 m_projMat;
    glm::mat4 m_viewMat;
    glm::mat4 m_modelMat;
    glm::mat3 m_normMat;

    // OpenGL VAO and BO's LBW skinned mesh
    QOpenGLVertexArrayObject m_meshVAO[NUMRENDERTYPES];
    QOpenGLBuffer m_meshVBO[NUMRENDERTYPES];
    QOpenGLBuffer m_meshNBO[NUMRENDERTYPES];
    QOpenGLBuffer m_meshIBO[NUMRENDERTYPES];
    QOpenGLBuffer m_meshBWBO[NUMRENDERTYPES];
    QOpenGLBuffer m_meshCBO[NUMRENDERTYPES];

    // VAO and BO's for iso-surface global mesh
    std::shared_ptr<QOpenGLVertexArrayObject> m_meshIsoVAO;
    std::shared_ptr<QOpenGLBuffer> m_meshIsoVBO;
    std::shared_ptr<QOpenGLBuffer> m_meshIsoNBO;

    // Shader locations
    GLuint m_vertAttrLoc[NUMRENDERTYPES];
    GLuint m_normAttrLoc[NUMRENDERTYPES];
    GLuint m_boneIDAttrLoc[NUMRENDERTYPES];
    GLuint m_boneWeightAttrLoc[NUMRENDERTYPES];
    GLuint m_boneUniformLoc[NUMRENDERTYPES];
    GLuint m_colourLoc[NUMRENDERTYPES];
    GLuint m_colourAttrLoc[NUMRENDERTYPES];
    GLuint m_projMatrixLoc[NUMRENDERTYPES];
    GLuint m_mvMatrixLoc[NUMRENDERTYPES];
    GLuint m_normalMatrixLoc[NUMRENDERTYPES];
    GLuint m_lightPosLoc[NUMRENDERTYPES];

    QOpenGLShaderProgram* m_shaderProg[NUMRENDERTYPES];
};

#endif // MODEL_H
