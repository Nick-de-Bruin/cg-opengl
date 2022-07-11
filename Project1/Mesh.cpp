#include "Mesh.h"

void Mesh::Render(const glm::mat4 &view /*, GLuint uniform_mv*/)
{
    // TODO: Apply transformations
    glm::mat4 mv = view * model;

    // Send mv -> We probbaly wanna do something other than a
    // uniform here, because uniform would be
    // for everything, would be bad:tm:
    // glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

