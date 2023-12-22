#version 460 core
const float PI = 3.14159265358979323846f;
const int Y_SEGMENTS = 10;
const int X_SEGMENTS = 10;

layout (points) in;
layout (triangle_strip, max_vertices = (Y_SEGMENTS + 1) * (X_SEGMENTS + 1)) out;

uniform float radius;

//flat in int ballIndex[];  // С����������
//flat out int BallIndex;  // С������
//out vec2 TexCoord;  // ��������

void generateSpherePoints(vec3 center, float radius, int ballIndex) {
    for (int i = 0; i <= Y_SEGMENTS; ++i) {
        for (int j = 0; j <= X_SEGMENTS; ++j) {
            // ʹ�������ֶ����õ�����˳��
            int index = i * (X_SEGMENTS + 1) + j;
            float xSegment = float(j) / float(X_SEGMENTS);
            float ySegment = float(i) / float(Y_SEGMENTS);
            float xPos = center.x + radius * cos(xSegment * 2.0 * PI) * sin(ySegment * PI);
            float yPos = center.y + radius * cos(ySegment * PI);
            float zPos = center.z + radius * sin(xSegment * 2.0 * PI) * sin(ySegment * PI);
            gl_Position = vec4(xPos, yPos, zPos, 1.0);

//            // ������������
//            TexCoord = vec2(xSegment, ySegment);
//            BallIndex = ballIndex;

            EmitVertex();
        }
    }
}

void main() {
    vec3 center = gl_in[0].gl_Position.xyz;  // ��ȡ�������λ��    
//    generateSpherePoints(center, radius, ballIndex[0]);  // ע������ʹ�� ballIndex[0]
    generateSpherePoints(center, radius, 0);
    EndPrimitive();
}
