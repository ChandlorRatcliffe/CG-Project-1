#include "commonLibs.h"
#include <vector>
int main() {
	float v1[2] = { 1.8, 6.2 };
	float v2[2] = { 1.8, 6.2 };
	float v3[2] = { 1.8, 6.2 };
	TranslationMatrix T = TranslationMatrix(1.5, 6.2);
	RotationMatrix    R = RotationMatrix(45.0);
	ScaleMatrix       S = ScaleMatrix(2.0, 3.0);
	ShearXMatrix     SX = ShearXMatrix(1.25);
	ShearYMatrix     SY = ShearYMatrix(1.25);
	CompositeMatrix   C = CompositeMatrix();

	std::vector<TransformationMatrix> transformations = std::vector<TransformationMatrix>();
	transformations.push_back(T);
	transformations.push_back(R);
	transformations.push_back(S);
	transformations.push_back(SX);
	transformations.push_back(SY);

	for (int i = 0; i < transformations.size(); ++i)
		C.composeWith(&transformations[i]);
	
	C.applyTo(v1);

	for (int i = 0; i < transformations.size(); ++i)
		transformations[i].applyTo(v2);

	for (int i = transformations.size()-1; i > -1 ; --i)
		transformations[i].applyTo(v3);

	std::cout << "v1 = <" << v1[0] << ", " << v1[1] << ">\r\n";
	std::cout << "v2 = <" << v2[0] << ", " << v2[1] << ">\r\n";
	std::cout << "v3 = <" << v3[0] << ", " << v3[1] << ">\r\n";

	//v1 should equal v3. v2 should be the odd one out.

	return 0;
}