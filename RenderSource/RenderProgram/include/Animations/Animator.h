#ifndef ANIMATOR_H
#define	ANIMATOR_H

#include <Animations/Animation.h>

class Animator {

public:

	Animator(Animation* animation);
	void UpdateAnimation(float dt);
	void PlayAnimation(Animation* pAnimation);
	void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);

	std::vector<glm::mat4> GetFinalBoneMatrices();

private:
	std::vector<glm::mat4> m_FinalBoneMatrices;
	Animation* m_CurrentAnimation;
	std::map<std::string, BoneInfo> currentBoneInfoMap;
	float m_CurrentTime;
	float m_DeltaTime;
};

#endif