#include<iostream>
#include<ctime>
#include<string>
#include <time.h>
#include <math.h>
#include <fstream>
#include "./autodiff/node.h"
#include"./matrix/matrix_def.h"
#include"./matrix/matrix_pro.h"
#include"./welcome/score_wel.cpp"
#include"./logistic/logistic_def.h"
#include"./file_pro/data_read.h"
#include"./grad_edge/matrix_grad.h"
using namespace std;
clock_t start, stop;
double duration;
Node z=1;
Node t1 = 1,a13 = 1;
Node loss_act(Node t1,Node a13)
{
	 Node loss = 0.5*(pow((t1-a13),2));
	 return loss;
}
Node sigmoid_act(Node z)
{
Node sigmoid_act = 1/(1+(1/exp(z)));
return sigmoid_act;
}
Node (*loss)(Node,Node) = loss_act;
Node (*act)(Node) = sigmoid_act;
int main()
{
	cout<<"------------autodiff for neraul network-----------"<<endl;
	Matrix data_mine = CreateMatrix(2,1);
	change_va(data_mine,0,0,0.55);
	change_va(data_mine,1,0,0.2);
	cout<<"data mine"<<endl;
	cout_mat(data_mine);
	cout<<"data mine"<<endl;
	Matrix label = CreateRandMat(2,1);
    change_va(label,0,0,0.4);
	change_va(label,1,0,0.8);
	Matrix weight1 = CreateRandMat(2,2);
	change_va(weight1,0,0,0.1);
	change_va(weight1,0,1,0.2);
	change_va(weight1,1,0,0.2);
	change_va(weight1,1,1,0.4);
	Matrix bais1 = ones(2,1);
	Matrix weight2 = CreateRandMat(2,2);
	change_va(weight2,0,0,0.5);
	change_va(weight2,1,0,0.6);
    change_va(weight2,0,1,0.7);
	change_va(weight2,1,1,0.8);
	Matrix bais2 = ones(2,1);
	for(int epoch = 0;epoch<1;epoch++)
	{
	cout<<"---------epoch: "<<epoch<<"------------"<<endl;
	cout_mat(weight1);
	int input_dim = 2;
	int output_dim = 2;
	edge_network sequaltial(input_dim,output_dim);
	Matrix output1 = sequaltial.forward(data_mine,weight1,bais1);
	//output1 acti_val;
	Matrix output1_without_act = sequaltial.forward_without_act(data_mine,weight1,bais1);
	//output1_without_act without activation;
	Matrix output2 = sequaltial.forward(output1,weight2,bais2);
	Matrix output2_without_act = sequaltial.forward_without_act(output1,weight2,bais2);	
	Matrix output_end = sequaltial.end_layer_backward(label,output2_without_act,*loss,*act);
	//last output layer should feed the value without activation;
	//output_end : the gradient of loss layer;
	Matrix backward3 = sequaltial.backward(output_end,output1_without_act,weight2,*act);
	//backward3: the gradient of the behind layer;
	Matrix weight_2_grad = mul(output_end,get_T(output1));
	Matrix weight_1_grad = mul(backward3,get_T(data_mine));
	weight1 = subtract(weight1,times_mat(0.001,weight_1_grad));
	bais1 = subtract(bais1,times_mat(0.001,backward3));
	weight2 = subtract(weight2,times_mat(0.001,weight_2_grad));
	bais2 = subtract(bais2,times_mat(0.001,output_end));
	cout<<"neraul end;"<<endl;
	return 0;
	}
}
