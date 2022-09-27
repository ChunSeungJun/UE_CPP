
#pragma once

#include "CoreMinimal.h"
// CooreMinimal : Engine ���� ����� �� �ִ� �⺻ ��ɵ��� ��Ƴ��� ����
#include "GameFramework/Actor.h"
// Actor : ���忡 ��ġ�� �� �ִ� ����� ��Ƴ��� ����
#include "C001_Spawn.generated.h"
// Generated : ���ø�����Ʈ�� �����Ϳ��� �ش� ������ �ִٴ� ���� �˷��ִ� ����

/*
class template : cpp �� h �� ���� �̸����� �����

.h   : ��������� ������ �ۼ� , ���е�� �� �� �ִ� �ൿ�� �̸� �ۼ�
Header File : �̸� ������� ��ɵ��� ��Ƴ��� ���Ϸ� #include �� �߰��ϰ�
			  �ȴٸ� �ش� ���Ͽ��� ��ɵ��� ����� �� �ֽ��ϴ�.

.cpp : �ൿ���� ��ü���� ����� �ۼ�
*/

// UCLASS() : Unreal �� ����� �� �ִ� class ��� ���� ���
UCLASS()
class UE_CPP_API AC001_Spawn : public AActor
{
	GENERATED_BODY()
	// GENERATED_BODY()
	// �ش� ��ġ���� class �� ��ü��� ���� ����մϴ�.
	
private :
	/*
	UPROPERTY() : Reflection ����� ����� �� �ִ� Ű�����Դϴ�.
				  UPROPERTY �� ��õ��� ���� �������� �����Ϳ��� �������� �ʽ��ϴ�.

	Unreal ������ ������ Ÿ���� �����մϴ�.
	1. C++ Ÿ�� : C++ �� �̷���� �ڵ带 ���մϴ�.
	2. ��Ű Ÿ�� : C++ �ڵ带 ���̽��� ������� �������Ʈ�� ���մϴ�.
	3. �ν��Ͻ� Ÿ�� : ��Ű Ÿ������ ���忡 ��ġ�Ǿ� �ִ� �������� ������ ���մϴ�.

	EditAnywhere	 : ��Ű Ÿ�� , �ν��Ͻ� Ÿ�Կ��� ��� �����ϸ� ������ �����մϴ�.
	EditInstanceOnly : �ν��Ͻ� Ÿ�Կ����� �����ϸ� ������ �����մϴ�.
	EditDefaultsOnly : ��Ű Ÿ�Կ����� �����ϸ� ������ �����մϴ�.
	VisibleAnywhere  : ��Ű Ÿ�� , �ν��Ͻ� Ÿ�Կ��� ��� �����ϸ� ������ �Ұ����մϴ�.
	*/


	UPROPERTY(EditAnywhere)		
		int A = 10;
	UPROPERTY(EditInstanceOnly) 
		int B = 20;
	UPROPERTY(EditDefaultsOnly) 
		int C = 30;
	UPROPERTY(VisibleAnywhere)	
		int D = 40;

	int E = 50;


	/*
	
	Actor �� ����� ���� Variable �̶�� Ŭ������ �����ϰ�
	�ɹ� ���� Var1, Var2, Var3, Var4 �� �������ּ���.

	Var1 �� ��ŰŸ�԰� �ν��Ͻ�Ÿ�Կ��� �����ϰ� ������ �Ұ����Ͽ��� �մϴ�.
	Var2 �� ��ŰŸ�Կ��� �����ϰ� ������ �����Ͽ��� �մϴ�.
	Var3 �� ��ŰŸ�԰� �ν��Ͻ�Ÿ�Կ��� �����ϰ� ������ �����Ͽ��� �մϴ�.
	Var4 �� �ν��Ͻ�Ÿ�Կ��� �����ϰ� ������ �����Ͽ��� �մϴ�.
	
	
	
	*/


public:	
	AC001_Spawn();
	/*
	������(Constructor) : ��ü�� ������ �� �� �ѹ� ȣ���ϴ� �Լ��Դϴ�.
	                     Ŭ������� ���� �̸��� �Լ��Դϴ�.
	
	��ü(Object) : ��� ������ �̷���� ����Ʈ����� ��ü�ϴ� �޸�
	*/          

protected:
	//	BeginPlay() : ������ ���۵� �� �� �ѹ� ȣ���ϴ� �Լ��Դϴ�.
	virtual void BeginPlay() override;

public:	
	// Tick() ���� ���� �� �� �����Ӹ��� ȣ���ϴ� �Լ��Դϴ�.
	virtual void Tick(float DeltaTime) override;

};
