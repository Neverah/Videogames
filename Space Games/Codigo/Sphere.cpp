///////////////////////////////////////////////////////////////////////////////
// Sphere.cpp
// ==========
// sphere for OpenGL with (radius, sectors, stacks)
// The min number of sectors is 3 and The min number of stacks are 2.
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2017-11-01
// UPDATED: 2018-03-23
///////////////////////////////////////////////////////////////////////////////
#pragma warning(disable:4996)
#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <math.h> 
#include "Sphere.h"

//Para las transformaciones
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#ifdef _WIN32
#include <windows.h>    // include windows.h to avoid thousands of compile errors even though this class is not depending on Windows
#endif



#include <iostream>
#include <iomanip>
#include <cmath>
#include "Sphere.h"



// constants //////////////////////////////////////////////////////////////////
const int MIN_SECTOR_COUNT = 3;
const int MIN_STACK_COUNT  = 2;



///////////////////////////////////////////////////////////////////////////////
// ctor
///////////////////////////////////////////////////////////////////////////////
Sphere::Sphere(float radius, int sectors, int stacks, bool smooth) : interleavedStride(32)
{
    set(radius, sectors, stacks, smooth);
}



///////////////////////////////////////////////////////////////////////////////
// setters
///////////////////////////////////////////////////////////////////////////////
void Sphere::set(float radius, int sectors, int stacks, bool smooth)
{
    this->radius = radius;
    this->sectorCount = sectors;
    if(sectors < MIN_SECTOR_COUNT)
        this->sectorCount = MIN_SECTOR_COUNT;
    this->stackCount = stacks;
    if(sectors < MIN_STACK_COUNT)
        this->sectorCount = MIN_STACK_COUNT;
    this->smooth = smooth;

    if(smooth)
        buildVerticesSmooth();
    else
        buildVerticesFlat();
}

void Sphere::setRadius(float radius)
{
    this->radius = radius;
    updateRadius();
}

void Sphere::setSectorCount(int sectors)
{
    set(radius, sectors, stackCount, smooth);
}

void Sphere::setStackCount(int stacks)
{
    set(radius, sectorCount, stacks, smooth);
}

void Sphere::setSmooth(bool smooth)
{
    if(this->smooth == smooth)
        return;

    this->smooth = smooth;
    if(smooth)
        buildVerticesSmooth();
    else
        buildVerticesFlat();
}



///////////////////////////////////////////////////////////////////////////////
// print itself
///////////////////////////////////////////////////////////////////////////////
void Sphere::printSelf() const
{
    std::cout << "===== Sphere =====\n"
              << "        Radius: " << radius << "\n"
              << "  Sector Count: " << sectorCount << "\n"
              << "   Stack Count: " << stackCount << "\n"
              << "Smooth Shading: " << (smooth ? "true" : "false") << "\n"
              << "Triangle Count: " << getTriangleCount() << "\n"
              << "   Index Count: " << getIndexCount() << "\n"
              << "  Vertex Count: " << getVertexCount() << "\n"
              << "  Normal Count: " << getNormalCount() << "\n"
              << "TexCoord Count: " << getTexCoordCount() << std::endl;
}



///////////////////////////////////////////////////////////////////////////////
// draw a sphere in VertexArray mode
// OpenGL RC must be set before calling it
///////////////////////////////////////////////////////////////////////////////
void Sphere::draw() const
{


	unsigned int VAOTriangulo;
	unsigned int VBO, EBO;

	glGenVertexArrays(1,  &VAOTriangulo);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAOTriangulo);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, interleavedVertices.size()*4, &interleavedVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	//// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// position Color

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	
	
	glBindVertexArray(VAOTriangulo);
glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
glDeleteVertexArrays(1, &VAOTriangulo);


}

void Sphere::drawHalf() const
{

    unsigned int VAOTriangulo;
    unsigned int VBO, EBO;

    glGenVertexArrays(1, &VAOTriangulo);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAOTriangulo);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, interleavedVertices.size() * 4, &interleavedVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    //// position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // position Color

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);


    glBindVertexArray(VAOTriangulo);
    glDrawElements(GL_TRIANGLES, indices.size()/2, GL_UNSIGNED_INT, 0);
    glDeleteVertexArrays(1, &VAOTriangulo);


}



///////////////////////////////////////////////////////////////////////////////
// update vertex positions only
///////////////////////////////////////////////////////////////////////////////
void Sphere::updateRadius()
{
    float scale = sqrtf(radius * radius / (vertices[0] * vertices[0] + vertices[1] * vertices[1] + vertices[2] * vertices[2]));

    std::size_t i, j;
    std::size_t count = vertices.size();
    for(i = 0, j = 0; i < count; i += 3, j += 8)
    {
        vertices[i]   *= scale;
        vertices[i+1] *= scale;
        vertices[i+2] *= scale;

        // for interleaved array
        interleavedVertices[j]   *= scale;
        interleavedVertices[j+1] *= scale;
        interleavedVertices[j+2] *= scale;
    }
}



///////////////////////////////////////////////////////////////////////////////
// build vertices of sphere with smooth shading using parametric equation
// x = r * cos(u) * cos(v)
// y = r * cos(u) * sin(v)
// z = r * sin(u)
// where u: stack(latitude) angle (-90 <= v <= 90)
//       v: sector(longitude) angle (0 <= u <= 360)
///////////////////////////////////////////////////////////////////////////////
void Sphere::buildVerticesSmooth()
{
    const float PI = 3.1415926f;

    // clear memory of prev arrays
    std::vector<float>().swap(vertices);
    std::vector<float>().swap(normals);
    std::vector<float>().swap(texCoords);
    std::vector<unsigned int>().swap(indices);
    std::vector<unsigned int>().swap(lineIndices);

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // normal
    float s, t;                                     // texCoord

    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coods
        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;

            // vertex position
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // vertex normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            // vertex tex coord
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            texCoords.push_back(s);
            texCoords.push_back(t);
        }
    }

    // indices
    unsigned int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if(i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if(i != (stackCount-1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }

            // vertical lines for all stacks
            lineIndices.push_back(k1);
            lineIndices.push_back(k2);
            if(i != 0)  // horizontal lines except 1st stack
            {
                lineIndices.push_back(k1);
                lineIndices.push_back(k1 + 1);
            }
        }
    }

    // generate interleaved vertex array as well
    buildInterleavedVertices();
}



///////////////////////////////////////////////////////////////////////////////
// generate vertices with flat shading
// each triangle is independent (no shared vertices)
///////////////////////////////////////////////////////////////////////////////
void Sphere::buildVerticesFlat()
{
    const float PI = 3.1415926f;

    // temp arrays
    std::vector<float> tmpVertices;
    std::vector<float> tmpTexCoords;

    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        float xy = radius * cosf(stackAngle);       // r * cos(u)
        float z = radius * sinf(stackAngle);        // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coods
        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;

            // vertex position
            tmpVertices.push_back(xy * cosf(sectorAngle));      // x = r * cos(u) * cos(v)
            tmpVertices.push_back(xy * sinf(sectorAngle));      // y = r * cos(u) * sin(v)
            tmpVertices.push_back(z);                           // z = r * sin(u)

            // vertex tex coord
            tmpTexCoords.push_back((float)j/sectorCount);       // s
            tmpTexCoords.push_back((float)i/stackCount);        // t
        }
    }

    // clear memory of prev arrays
    std::vector<float>().swap(vertices);
    std::vector<float>().swap(normals);
    std::vector<float>().swap(texCoords);
    std::vector<unsigned int>().swap(indices);
    std::vector<unsigned int>().swap(lineIndices);

    float x1,y1,z1, x2,y2,z2, x3,y3,z3, x4,y4,z4;   // 4 vertex positions v1, v2, v3, v4
    float s1, t1, s2, t2, s3, t3, s4, t4;           // 4 tex coords
    std::vector<float> n;                           // 1 face normal

    int i, j, k, vi1, vi2, ti1, ti2;
    int index = 0;                                  // index for vertex
    for(i = 0; i < stackCount; ++i)
    {
        vi1 = i * (sectorCount + 1) * 3;            // index of tmpVertices
        vi2 = (i + 1) * (sectorCount + 1) * 3;
        ti1 = i * (sectorCount + 1) * 2;            // index of tmpTexCoords
        ti2 = (i + 1) * (sectorCount + 1) * 2;

        for(j = 0; j < sectorCount; ++j, vi1+=3, vi2+=3, ti1+=2, ti2+=2)
        {
            // v1
            x1 = tmpVertices[vi1];
            y1 = tmpVertices[vi1 + 1];
            z1 = tmpVertices[vi1 + 2];
            s1 = tmpTexCoords[ti1];
            t1 = tmpTexCoords[ti1 + 1];

            // v2
            x2 = tmpVertices[vi2];
            y2 = tmpVertices[vi2 + 1];
            z2 = tmpVertices[vi2 + 2];
            s2 = tmpTexCoords[ti2];
            t2 = tmpTexCoords[ti2 + 1];

            // v3
            x3 = tmpVertices[vi1 + 3];
            y3 = tmpVertices[vi1 + 4];
            z3 = tmpVertices[vi1 + 5];
            s3 = tmpTexCoords[ti1 + 2];
            t3 = tmpTexCoords[ti1 + 3];

            // v4
            x4 = tmpVertices[vi2 + 3];
            y4 = tmpVertices[vi2 + 4];
            z4 = tmpVertices[vi2 + 5];
            s4 = tmpTexCoords[ti2 + 2];
            t4 = tmpTexCoords[ti2 + 3];

            // compute a face normal
            if(i == 0)  // first stack
                n = computeFaceNormal(x3,y3,z3, x2,y2,z2, x4,y4,z4);
            else
                n = computeFaceNormal(x1,y1,z1, x2,y2,z2, x3,y3,z3);

            // if 1st stack and last stack, store only 1 triangle per sector
            // otherwise, store 2 triangles (quad) per sector
            if(i > 0 && i < (stackCount-1))
            {
                // put quad vertices: v1-v2-v3-v4
                vertices.push_back(x1);
                vertices.push_back(y1);
                vertices.push_back(z1);
                vertices.push_back(x2);
                vertices.push_back(y2);
                vertices.push_back(z2);
                vertices.push_back(x3);
                vertices.push_back(y3);
                vertices.push_back(z3);
                vertices.push_back(x4);
                vertices.push_back(y4);
                vertices.push_back(z4);

                // put tex coords of quad
                texCoords.push_back(s1);
                texCoords.push_back(t1);
                texCoords.push_back(s2);
                texCoords.push_back(t2);
                texCoords.push_back(s3);
                texCoords.push_back(t3);
                texCoords.push_back(s4);
                texCoords.push_back(t4);

                // put normal
                for(k = 0; k < 4; ++k)  // same normals for 4 vertices
                {
                    normals.push_back(n[0]);
                    normals.push_back(n[1]);
                    normals.push_back(n[2]);
                }

                // put indices of quad
                indices.push_back(index);
                indices.push_back(index+1);
                indices.push_back(index+2);
                indices.push_back(index+2);
                indices.push_back(index+1);
                indices.push_back(index+3);

                // indices for lines
                lineIndices.push_back(index);
                lineIndices.push_back(index+1);
                lineIndices.push_back(index);
                lineIndices.push_back(index+2);

                index += 4;     // for next
            }
            else
            {
                // put a triangle
                vertices.push_back(x1);
                vertices.push_back(y1);
                vertices.push_back(z1);
                vertices.push_back(x2);
                vertices.push_back(y2);
                vertices.push_back(z2);
                if(i == 0)  // first stack
                {
                    vertices.push_back(x4);
                    vertices.push_back(y4);
                    vertices.push_back(z4);
                }
                else        // last stack
                {
                    vertices.push_back(x3);
                    vertices.push_back(y3);
                    vertices.push_back(z3);
                }

                // put tex coords of triangle
                texCoords.push_back(s1);
                texCoords.push_back(t1);
                texCoords.push_back(s2);
                texCoords.push_back(t2);
                if(i == 0)  // first stack
                {
                    texCoords.push_back(s4);
                    texCoords.push_back(t4);
                }
                else        // last stack
                {
                    texCoords.push_back(s3);
                    texCoords.push_back(t3);
                }

                // put normal
                for(k = 0; k < 3; ++k)  // same normals for 3 vertices
                {
                    normals.push_back(n[0]);
                    normals.push_back(n[1]);
                    normals.push_back(n[2]);
                }

                // put indices of 1 triangle
                indices.push_back(index);
                indices.push_back(index+1);
                indices.push_back(index+2);

                // indices for lines
                lineIndices.push_back(index);
                lineIndices.push_back(index+1);
                if(i == (stackCount - 1))   // last stack requires both vert/hori lines
                {
                    lineIndices.push_back(index);
                    lineIndices.push_back(index+2);
                }

                index += 3;     // for next
            }
        }
    }

    // generate interleaved vertex array as well
    buildInterleavedVertices();
}



///////////////////////////////////////////////////////////////////////////////
// generate interleaved vertices: V/N/T
// stride must be 32 bytes
///////////////////////////////////////////////////////////////////////////////
void Sphere::buildInterleavedVertices()
{
    std::vector<float>().swap(interleavedVertices);

    std::size_t i, j;
    std::size_t count = vertices.size();
    for(i = 0, j = 0; i < count; i += 3, j += 2)
    {
        interleavedVertices.push_back(vertices[i]);
        interleavedVertices.push_back(vertices[i+1]);
        interleavedVertices.push_back(vertices[i+2]);

        interleavedVertices.push_back(normals[i]);
        interleavedVertices.push_back(normals[i+1]);
        interleavedVertices.push_back(normals[i+2]);

        interleavedVertices.push_back(texCoords[j]);
        interleavedVertices.push_back(texCoords[j+1]);
    }
}



///////////////////////////////////////////////////////////////////////////////
// return face normal of a triangle v1-v2-v3
// if a triangle has no surface (normal length = 0), then return a zero vector
///////////////////////////////////////////////////////////////////////////////
std::vector<float> Sphere::computeFaceNormal(float x1, float y1, float z1,  // v1
                                             float x2, float y2, float z2,  // v2
                                             float x3, float y3, float z3)  // v3
{
    const float EPSILON = 0.000001f;

    std::vector<float> normal(3, 0.0f);     // default return value (0,0,0)
    float nx, ny, nz;

    // find 2 edge vectors: v1-v2, v1-v3
    float ex1 = x2 - x1;
    float ey1 = y2 - y1;
    float ez1 = z2 - z1;
    float ex2 = x3 - x1;
    float ey2 = y3 - y1;
    float ez2 = z3 - z1;

    // cross product: e1 x e2
    nx = ey1 * ez2 - ez1 * ey2;
    ny = ez1 * ex2 - ex1 * ez2;
    nz = ex1 * ey2 - ey1 * ex2;

    // normalize only if the length is > 0
    float length = sqrtf(nx * nx + ny * ny + nz * nz);
    if(length > EPSILON)
    {
        // normalize
        float lengthInv = 1.0f / length;
        normal[0] = nx * lengthInv;
        normal[1] = ny * lengthInv;
        normal[2] = nz * lengthInv;
    }

    return normal;
}
