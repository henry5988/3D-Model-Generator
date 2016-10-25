#ifndef COLOREDVERTEX_H
#define COLOREDVERTEX_H
#include<stdio.h>
#include<iostream>
#include"votingmatrix.h"

#include <vector>

class VotingNode {
public:

	void addVoter(MatrixNode voter) {
		voters.push_back(voter);
		float red = 0, green = 0, blue = 0, count = 0;
		//set colors to be the average value

        for(int i=0; i<voters.size();  i++) {
			count++;
            red += voters[i].getColor(0);
            green += voters[i].getColor(1);
            blue += voters[i].getColor(2);
		}
		colors[0] = round(red / count);
		colors[1] = round(green / count);
		colors[2] = round(blue / count);
	}
	uint8_t getColor(int RGorB_ZeroToTwo) {
		//0R 1G 2B
		if (RGorB_ZeroToTwo > 2)
		{
			std::cerr << "ERROR RGorB_ZeroToTwo must be between 1(red) and 2(blue)";
		}
		return colors[RGorB_ZeroToTwo];
	}
	float getWeight() {
		float weight = 0;
        foreach(MatrixNode v , voters) {
			weight += v.getWeight();
		}
		return weight;

	}

    void printValues(){

        std::cout<<"R:"<<(int)colors[0]<<" G:"<<(int)colors[1]<<" B:"<<(int)colors[2]<<"Weight:"<<getWeight()<<std::endl;
    }

private:
	std::vector<MatrixNode> voters;
	uint8_t colors[3];
};


class ColoredVertex {//represents a color at a certain point on the Matrix
public:
	ColoredVertex(int w, int h, int d) {
		width = w;
		height = h;
		depth = d;
	}
    uint8_t* getValue(){return value;}
	void addVoter(MatrixNode voter) { voters.push_back(voter); }
	void setValueFromVoters(int grouping_tollerance) {
        //group together nodes based on similar colors
        std::vector<VotingNode> groupedVoters;
		for (int i = 0; i < voters.size(); i++) {
			int closest_group_index = -1, closest_size = -1;//find the group that matches the color the best

			for (int j = 0; j < groupedVoters.size(); j++) {
				int contrast = (voters[i].colorContrast(groupedVoters[j].getColor(0), groupedVoters[j].getColor(1), groupedVoters[j].getColor(2)));
				if (contrast <= grouping_tollerance) {
					if (contrast < closest_size || closest_size == -1) {
						closest_size = contrast;
						closest_group_index = j;
					}
				}

			}
			if (closest_size == -1) {
				VotingNode temp = VotingNode();
				temp.addVoter(voters[i]);
				groupedVoters.push_back(temp);

			}
			else
			{
				groupedVoters[closest_group_index].addVoter(voters[i]);

			}
		}

        //compare the votes of the groups and chose the group with the highest combined weight
		int greatest_vote_weight = -1, index_of_vote = -1;
		for (int i = 0; i < groupedVoters.size(); i++) {
			if (groupedVoters[i].getWeight() > greatest_vote_weight) {
				greatest_vote_weight = groupedVoters[i].getWeight();
				index_of_vote = i;
			}
		}
		VotingNode winner = groupedVoters[index_of_vote];
		value = new uint8_t[4];
		value[0] = winner.getColor(0);
		value[1] = winner.getColor(1);
		value[2] = winner.getColor(2);
		value[3] = 1;
	}
    int getX(){return width;}

    int getY(){return height;}
    int getZ(){return depth;}
    void printVert(){std::cout<<"x: "<<width<<"y: "<<height<<"z: "<<depth<<endl;}
protected:


private:
	uint8_t* value;
	std::vector<std::vector<ColoredVertex>> faces;
	std::vector<MatrixNode> voters;
    int width, height, depth;

};
#endif
