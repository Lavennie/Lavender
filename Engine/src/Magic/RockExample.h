#pragma once
#include <list>
#include <string>
using namespace std;

namespace Lavender {

	class TempComponents {

	};
	class Transform :public TempComponents {

	};
	class TempSceneObject {
		std::list<TempSceneObject> components;

	public:
		void Add(Transform transform) {

		}
	};



	class DataEngine {
	public:
		static void GetObj(TempSceneObject* obj, string ref) {

		}
		static void GetComp(TempComponents* comp, string ref) {

		}
	};

	class RockExample: public TempSceneObject
	{
		void Update() {
		}
	};

	
	class BlackHole {
		void BlackHoleEffect(TempSceneObject target) {
			//float dist = GetDist(target, this);
		}

		void GetDist(TempSceneObject* o1, TempComponents* t1) {
			string str1 = "xyz"s;
			string str2 = "xyz"s;
			DataEngine::GetObj(o1, str1);
			DataEngine::GetComp(t1, str2);
		}
	};


	class ObjectFactory {
		void CreateTransform(TempSceneObject tso) {
			//tso.Add(new Transform());
		}
	};

}

