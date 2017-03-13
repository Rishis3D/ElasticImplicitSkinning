#ifndef IMPLICITSKINDEFORMER_H
#define IMPLICITSKINDEFORMER_H

#include <cuda_runtime.h>
#include <cuda.h>
#include <cuda_gl_interop.h>

#include "mesh.h"
//#include "ScalarField/globalfieldfunction.h"


/// @author Idris Miles
/// @version 1.0


/// @class ImplicitSkinDeformer
/// @brief This class deforms a mesh using the implicit skinning technique.
class ImplicitSkinDeformer
{
public:
    /// @brief Constructor.
    ImplicitSkinDeformer(const Mesh _origMesh,
                        const GLuint _meshVBO,
                        const std::vector<glm::mat4> &_transform);

    /// @brief Destructor.
    ~ImplicitSkinDeformer();

    /// @brief Method to deform mesh.
    void Deform();

    /// @brief Method to perform LBW skinning
    /// @param _transform : a vector of joint transform matrices.
    void PerformLBWSkinning(const std::vector<glm::mat4> &_transform);

    /// @brief
    void PerformVertexProjection();

    /// @brief
    void PerformTangentialRelaxation();

    /// @brief
    void PerformLaplacianSmoothing();

private:

    //---------------------------------------------------------------------
    // Private Methods
    /// @brief Method to get the device side pointer to deformed mesh vertices for use in CUDA kernels
    glm::vec3 *GetMeshDeformedPtr();

    /// @brief Method to release the device side pointer so OpenGL can use the VBO holding the deformed mesh vertices.
    void ReleaseMeshDeformedPtr();


    //---------------------------------------------------------------------
    // Private Attributes
    /// @brief
    cudaGraphicsResource *m_meshVBO_CUDA;

    /// @brief
    glm::vec3 *d_meshDeformedPtr;

    /// @brief
    glm::vec3 *d_meshOrigPtr;

    /// @brief
    glm::mat4 *d_transformPtr;

    /// @brief
    unsigned int *d_boneIdPtr;

    /// @brief
    float *d_weightPtr;

    /// @brief
    bool m_meshDeformedMapped;

    /// @brief
    int m_numVerts;

//    GlobalFieldFunction m_gf;

    bool m_init;

};

#endif // IMPLICITSKINDEFORMER_H
