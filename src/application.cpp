#include "application.h"

#include <iostream>
#include <windows.h>
#include "graphics.h"
#include "constants.h"
#include "force.h"

Application::Application()
	:
	m_running(false),
	pushForces(0, 0),
	liquid(),
	m_mouseCursor(Vec2(0.f, 0.f)),
	isLeftButtonDown(false),
	selectedParticle(nullptr),
	m_k(40),
	m_restLenght(200),
	m_anchor(0.f, 0.f)
{

}

bool Application::IsRunning()
{
	return m_running;
}

void Application::Setup()
{
	m_running = Graphics::OpenWindow();
	m_anchor = Vec2(Graphics::Width() / 2.0f, 30);
	Particle* bob = new Particle(Graphics::Width() / 2.0f, Graphics::Height() / 2.0f, 2.0f);
	bob->radius = 10;
	m_particles.push_back(bob);

}

void Application::Input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				m_running = false;
			}
			if (event.key.keysym.sym == SDLK_UP)							
			{
				auto forceY = -50.f * Constant::PIXELS_PER_METER;
				pushForces.SetY(forceY);
			}
			if (event.key.keysym.sym == SDLK_DOWN)
			{
				auto forceY = 50.f * Constant::PIXELS_PER_METER;
				pushForces.SetY(forceY);
			}
			if (event.key.keysym.sym == SDLK_RIGHT)
			{
				auto forceX = 50.f * Constant::PIXELS_PER_METER;
				pushForces.SetX(forceX);
			}
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				auto forceX = -50.f * Constant::PIXELS_PER_METER;
				pushForces.SetX(forceX);
			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_UP)
			{
				pushForces.SetY(0.f);
			}
			if (event.key.keysym.sym == SDLK_DOWN)
			{
				pushForces.SetX(0.f);
			}
			if (event.key.keysym.sym == SDLK_RIGHT)
			{
				pushForces.SetY(0.f);
			}
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				pushForces.SetX(0.f);
			}
			break;

		/*//Generate new particle with random color and mass by loft click th mouse
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);

				//Generate random mass between 0.5 ~ 3.0
				float randomMass = 0.5f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (3.0f - 0.5f)));

				//Generate random radius between 3 and 10
				int randomRadius = 3 + (rand() % 8);		//random radius between 3 and 10. perhaps....

				Particle* particle = new Particle(x, y, randomMass);
				particle->radius = randomRadius;
				

				//Generate random color (ARGB format)
				Uint32 randomColor = 0xFF000000
					| ((rand() % 256) << 16)	// Red
					| ((rand() % 256) << 6)		// Green
					| (rand() % 256);			// Blue
				particle->color = randomColor;

				m_particles.push_back(particle);
			}
			break;
			*/

		case SDL_MOUSEBUTTONDOWN:
			if (!isLeftButtonDown && event.button.button == SDL_BUTTON_LEFT)
			{
				isLeftButtonDown = true;
				int x, y;
				SDL_GetMouseState(&x, &y);
				m_mouseCursor.SetX(x);
				m_mouseCursor.SetY(y);

				//check if click inside any ball
				for (auto particle : m_particles )
				{
					float distanceToBall = (particle->position - m_mouseCursor).Magnitude();
					if (distanceToBall <= particle->radius)
					{
						selectedParticle = particle;
						break;
					}
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (isLeftButtonDown && event.button.button == SDL_BUTTON_LEFT)
			{
				isLeftButtonDown = false;
				if (selectedParticle)
				{
					Vec2 impulseDirection = (selectedParticle->position - m_mouseCursor).UnitVector();
					float impulseMagnitude = (selectedParticle->position - m_mouseCursor).Magnitude() * 5.0f;
					selectedParticle->velocity = impulseDirection * impulseMagnitude;
					selectedParticle = nullptr;				// Clear the selection
				}
			}
			break;

			case SDL_MOUSEMOTION:
			m_mouseCursor.SetX(event.motion.x);
			m_mouseCursor.SetY(event.motion.y);
			break;
		}

	}
}

/*Called several times per second, meaning called per FPS */
void Application::Update()
{
	static float timePreviousFrame = 0.f;						
	static int frameCount = 0;
	static float fps = 0.0;
	static float timeAccumulator = 0.f;

	UINT64 currentTime = SDL_GetTicks64();
	float elapsedTime = static_cast<float>(currentTime) - timePreviousFrame;

	//Update timePreviousTime
	timePreviousFrame = currentTime;

	// Accumulated time for FPS calculation (after every second)
	timeAccumulator += elapsedTime;
	frameCount++;

	if (timeAccumulator >= 1000)
	{
		fps = frameCount / (timeAccumulator / 1000.0f);
		std::cout << "Current FPS= " << fps << "\n";

		//Reset Frame count for next second
		frameCount = 0;
		timeAccumulator = 0;
	}

	/* Check if we are move too fast, and if so, waste some milliseconds, yes we move too fast we need to slow it down until it reach MILLISECOND_PER_FRAME aka 1000/60 in this case */
	int timeToWait = Constant::MILLISECOND_PER_FRAME - (currentTime - timePreviousFrame);
	if (timeToWait > 0)
	{
		SDL_Delay(timeToWait);
	}

	float deltaTime = elapsedTime / 1000.f;
	if (deltaTime > Constant::maxDeltaTime)
	{
		deltaTime = Constant::maxDeltaTime;
	}

	for (auto particle: m_particles)
	{
		particle->AddForce(pushForces);

		/** Applying spring force */ 
		Vec2 drag = Force::GenerateDragForce(*particle, 0.001f);
		particle->AddForce(drag);
		Vec2 weight = Vec2(0.f, particle->mass * 9.8f * Constant::PIXELS_PER_METER);
		particle->AddForce(weight);

		//integrate velocity to estimate new position
		particle->Integrate(deltaTime);

		if (particle->position.GetX() - particle->radius <= 0)
		{
			particle->position.SetX(particle->radius);
			
			float velocityX = particle->velocity.GetX();
			particle->velocity.SetX(velocityX * -0.9f);
		}
		else if (particle-> position.GetX() + particle->radius >= Graphics::Width())
		{
			particle->position.SetX(Graphics::Width() - particle->radius);

			float velocityX = particle->velocity.GetX();
			particle->velocity.SetX(velocityX * -0.9f);
		}

		if (particle->position.GetY() - particle->radius <= 0)
		{
			particle->position.SetY(particle->radius);

			float velocityY = particle->velocity.GetY();
			particle->velocity.SetY(velocityY * -0.9f);
		}
		else if (particle->position.GetY() + particle->radius >= Graphics::Height())
		{
			particle->position.SetY(Graphics::Height() - particle->radius);

			float velocityY = particle->velocity.GetY();
			particle->velocity.SetY(velocityY * -0.9f);
		}
	}
	//Apply spring force
	Vec2 springForce = Force::GenerateSpringForce(m_particles[0], m_anchor, m_restLenght, m_k);
	m_particles[0]->AddForce(springForce);
}

void Application::Render()
{
	Graphics::ClearScreen(0x13746B);			//change the background color, but it's kinda complicated

	//Draw anchor
	Graphics::DrawFillCircle(m_anchor.GetX(), m_anchor.GetY(), 5, 0xFF001155);

	//Draw Bob
	Graphics::DrawFillCircle(m_particles[0]->position.GetX(), m_particles[0]->position.GetY(), m_particles[0]->radius, 0xFFFFFFFF);

	//Draw spring (just line)
	Graphics::DrawLine(m_anchor.GetX(), m_anchor.GetY(), m_particles[0]->position.GetX(), m_particles[0]->position.GetY(), 0xFF313131);

	Graphics::RenderFrame();
}

void Application::Destroy()
{
	for (auto particle: m_particles)
	{
		delete particle;
	}
	Graphics::CloseWindow();
}

