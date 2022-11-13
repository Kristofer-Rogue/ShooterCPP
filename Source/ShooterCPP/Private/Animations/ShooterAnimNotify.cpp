// ShooterGame. All Rights Reserved.


#include "Animations/ShooterAnimNotify.h"

void UShooterAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation, EventReference);
}
