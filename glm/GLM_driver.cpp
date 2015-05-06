#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <iostream>

std::string matToString(glm::mat4 & m){
	std::string msg = "";
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			msg = msg + std::to_string(m[i][j]) + " ";
		}
		msg = msg + "\n";
	}
	return msg;
}

glm::mat4 multiply(glm::mat4 & m, glm::mat4 & n){
	glm::mat4 temp;

	for(int i = 0; i < 4; i++){ 
		for(int j = 0; j < 4; j++){ 
			temp[i][j] = 0.0;
			for(int x = 0; x < 4; x++){
				temp[i][j] += m[i][x] * n[x][j]; 
			}
		} 
	} 
	return temp;
}

int main(){

	glm::mat4 m1, m2, res(0.0);

	float A[16] = {
		1.0, 2.0, 0.0, 1.0,
		0.0, 1.0, 2.0, 3.0,
		1.0, 4.0, 2.0, 5.0,
		0.0, 1.0, 0.0, 1.0
	};

	float B[16] = {
		1.0, 0.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 1.0,
		0.0, 1.0, 1.0, 1.0
	};
	
	memcpy( glm::value_ptr( m1 ), A, sizeof( A ) );
	memcpy( glm::value_ptr( m2 ), B, sizeof( B ) );

	std::cout << "m1 = " << std::endl << matToString(m1) << std::endl;
	std::cout << "m2 = " << std::endl << matToString(m2) <<std::endl;

	res = multiply(m1, m2);

	std::cout << "Res  m1 * m2 = " << std::endl << matToString(res) <<std::endl;
	system("pause"); 
	return 0;
}