// ShooterGame. All Rights Reserved.


#include "Animations/ShooterEquipFinishAnimNotify.h"

void UShooterEquipFinishAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation, EventReference);
}
