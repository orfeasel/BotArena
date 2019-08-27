# BotArena

Developed with Unreal Engine 4

![Bot Arena gif showcase](GitHubAssets/BotArena.gif)

AI Team Deathmatch. You can see a video preview of the project here: https://www.youtube.com/watch?v=e7ImcXDCv6U

**The animation pack is licensed for use with Unreal Engine only and it belongs to Epic Games [for more information visit this marketplace link] (https://www.unrealengine.com/marketplace/en-US/slug/animation-starter-pack)**

The level mockup material is credited to [Tom Looman] (https://www.tomlooman.com/) and is [available for download from here] (https://www.tomlooman.com/updated-mockup-material-for-unreal-4/)

Implemented features so far:
1. AI Senses:
..Hearing and
..Sight
2. A behavior tree that contains custom:
..AI Tasks and
..AI Services
3. Several Environent Queries and Environment Contexts in order for the bots to identify the best location that they need to reach based on several parameters:
..Their health
..Ammo count
..Their enemies position (so they can line of sight them in case they need to retreat)
4. Custom areas and nav links where each bot can decide to either crouch or stand