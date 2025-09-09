# InfoDrops Example Content Guide

This directory contains example HTML files for the InfoDrops device, along with instructions for creating your own content using the available CSS themes and styling options.

## 📁 Included Examples

- **`community_cohesion.html`** - Community organizing guide (uses `theme-light`)
- **`resist_fascism.html`** - Digital resistance guide (uses `theme-dossier`)

## 🎨 Available CSS Themes

The `minimal.css` file includes **six pre-built themes** you can apply by adding the appropriate class to your `<body>` tag:

### 1. `theme-dark` (Default)

- **Style**: Clean, modern dark theme with red accents
- **Colors**: Black backgrounds (#0d0d0d), light text (#e0e0e0), red borders (#ff4136)
- **Font**: Courier New (monospace)
- **Use for**: General information, technical guides, resistance content
- **Example**: `<body class="theme-dark">`

### 2. `theme-dossier` (Classified Document)

- **Style**: Official government document aesthetic
- **Colors**: White background (#ffffff), dark text (#111111), red accents (#c00000)
- **Font**: Georgia serif with Courier New headers
- **Use for**: Official information, serious documentation, formal announcements
- **Example**: `<body class="theme-dossier">`

### 3. `theme-light` (Community Friendly)

- **Style**: Warm, approachable community design
- **Colors**: Cream background (#f5f2e9), dark brown text (#3d3522), green accents (#2a7f62)
- **Font**: Serif with sans-serif headers
- **Use for**: Community organizing, mutual aid, local resources, welcoming content
- **Example**: `<body class="theme-light">`

### 4. `theme-chill` (Relaxed Aesthetic)

- **Style**: Cool, relaxed vibe with purple/blue color scheme
- **Colors**: Dark navy background (#1a1a2e), light text (#e0e0e0), purple accents (#9d8eee)
- **Font**: Segoe UI (modern sans-serif)
- **Use for**: Entertainment, creative content, laid-back information sharing
- **Example**: `<body class="theme-chill">`

### 5. `theme-professional` (Corporate Clean)

- **Style**: Clean, corporate, professional appearance
- **Colors**: Light gray background (#f4f7fa), dark text (#333), blue accents (#0056b3)
- **Font**: Arial (clean sans-serif)
- **Use for**: Business information, official announcements, professional guides
- **Example**: `<body class="theme-professional">`

### 6. `theme-undercover` (Hacker/Secret Agent)

- **Style**: Matrix-style green-on-black terminal aesthetic
- **Colors**: Pure black background (#000), bright green text (#0f0), glowing text effects
- **Font**: Lucida Console (monospace terminal font)
- **Use for**: Security guides, hacker culture, underground information, dramatic effect
- **Example**: `<body class="theme-undercover">`

## 🎭 Theme Comparison Quick Reference

| Theme          | Background | Text         | Accent   | Font              | Best For            |
| -------------- | ---------- | ------------ | -------- | ----------------- | ------------------- |
| `dark`         | Black      | Light Gray   | Red      | Courier New       | Technical, general  |
| `dossier`      | White      | Black        | Dark Red | Georgia + Courier | Official, formal    |
| `light`        | Cream      | Brown        | Green    | Serif             | Community, friendly |
| `chill`        | Navy       | Light Gray   | Purple   | Segoe UI          | Creative, relaxed   |
| `professional` | Light Gray | Dark Gray    | Blue     | Arial             | Business, corporate |
| `undercover`   | Black      | Bright Green | White    | Lucida Console    | Security, dramatic  |

## 📝 HTML Template Structure

Here's the basic structure for creating new InfoDrops content:

```html
<!DOCTYPE html>
<html lang="en">
	<head>
		<meta charset="UTF-8" />
		<meta
			name="viewport"
			content="width=device-width, initial-scale=1.0, user-scalable=no"
		/>
		<title>Your Content Title [v.1.0]</title>
		<link
			rel="stylesheet"
			href="../../data/minimal.css"
		/>
	</head>
	<body class="theme-dark">
		<!-- Choose your theme here -->
		<header>
			<!-- Language Switch (optional) -->
			<div class="lang-switch">
				<button
					id="lang-en"
					class="lang-btn"
					data-translate="lang_en"
				>
					English
				</button>
				<button
					id="lang-es"
					class="lang-btn"
					data-translate="lang_es"
				>
					Español
				</button>
			</div>

			<!-- Main Title -->
			<h1 data-translate="main_title">Your Title Here</h1>
			<p
				class="subtitle"
				data-translate="main_subtitle"
			>
				Your subtitle here
			</p>
		</header>

		<main>
			<section id="section1">
				<h2 data-translate="section1_title">Section Title</h2>
				<p data-translate="section1_subtitle">Section description</p>

				<!-- Expandable Content Blocks -->
				<details>
					<summary data-translate="item1_title">Click to Expand</summary>
					<div class="details-content">
						<p data-translate="item1_content">Your content here...</p>
					</div>
				</details>
			</section>
		</main>

		<footer>
			<p data-translate="footer_text">Footer information</p>
		</footer>

		<!-- Translation Script (if using multilingual) -->
		<script>
			// Add your translation object and language switching code here
		</script>
	</body>
</html>
```

## 🔧 Key HTML Elements & Styles

### Headers and Text

- `<h1>` - Main page title
- `<h2>` - Section titles
- `<h3>` - Subsection titles
- `.subtitle` - Subtitle styling for descriptions

### Expandable Content

```html
<details>
	<summary>Click to expand title</summary>
	<div class="details-content">
		<p>Hidden content goes here...</p>
		<ul>
			<li>List items get special bullet styling</li>
			<li>Automatically themed per your chosen style</li>
		</ul>
	</div>
</details>
```

### Language Support

```html
<!-- Language Switch Buttons -->
<div class="lang-switch">
	<button
		id="lang-en"
		class="lang-btn"
	>
		English
	</button>
	<button
		id="lang-es"
		class="lang-btn"
	>
		Español
	</button>
</div>

<!-- Translatable Elements -->
<p data-translate="translation_key">Default English text</p>
```

### Layout Structure

- `<header>` - Page header with title and language switch
- `<main>` - Main content area
- `<section>` - Content sections with auto-spacing
- `<footer>` - Page footer

## 🚀 Creating Your Own Content

### Step 1: Choose Your Theme

Decide which theme best fits your content:

- **General/Technical**: Use `theme-dark` (default, good for most content)
- **Official/Formal**: Use `theme-dossier` (serious, document-style)
- **Community/Friendly**: Use `theme-light` (warm, approachable)
- **Creative/Relaxed**: Use `theme-chill` (cool, laid-back)
- **Business/Professional**: Use `theme-professional` (corporate, clean)
- **Security/Underground**: Use `theme-undercover` (hacker, dramatic)

### Step 2: Copy the Template

1. Copy one of the example files as your starting point
2. Update the `<title>` and version number
3. Change the `<body class="">` to your chosen theme

### Step 3: Add Your Content

- Replace title and subtitle text
- Add your sections using `<section>` tags
- Use `<details>` blocks for expandable content
- Add `data-translate` attributes if you want multilingual support

### Step 4: Test Locally

1. Place your HTML file in the `example_info/` directory
2. Open in a web browser to test layout and functionality
3. Check that all themes work by changing the body class

### Step 5: Deploy to Device

1. Copy your finished HTML file to the `data/` directory
2. Upload to your ESP32 device
3. Access via the InfoDrops WiFi portal

## 🎨 Custom Styling Tips

### Adding New Themes

To create a new theme, add CSS rules to `minimal.css`:

```css
.theme-yourname {
	background: #your-bg-color;
	color: #your-text-color;
}

.theme-yourname header,
.theme-yourname section,
.theme-yourname footer {
	background: #section-bg-color;
	border: 1px solid #border-color;
}

/* Add more specific styling as needed */
```

### ESP32 Performance Tips

- Keep CSS simple - the device has limited processing power
- Avoid complex animations or transitions
- Use web-safe fonts (the CSS already includes good fallbacks)
- Test on mobile devices for responsive behavior

## 📱 Mobile-First Design

All themes are designed to work well on small screens:

- Responsive typography that scales appropriately
- Touch-friendly button sizes
- Readable text with good contrast ratios
- No horizontal scrolling required

## 🌍 Multilingual Support

To add multiple languages:

1. **Add translation object to your JavaScript**:

```javascript
const translations = {
	en: {
		main_title: 'English Title',
		section1_title: 'Section Title',
	},
	es: {
		main_title: 'Título en Español',
		section1_title: 'Título de Sección',
	},
};
```

2. **Add language switching functionality** (see example files for complete code)

3. **Mark translatable elements** with `data-translate="key"`

### File Paths

When creating content in `example_info/`, the CSS path should be:

- `href="../../data/minimal.css"` (from example_info directory)
- `href="/minimal.css"` (when deployed to ESP32 data directory)

## 💡 Content Ideas

### Recommended Topics

- Community resource guides
- Emergency preparedness information
- Local event announcements
- Digital privacy guides
- Mutual aid organizing
- Local business directories
- Neighborhood safety information
- Tool libraries and resource sharing

### Keep It Local

InfoDrops work best for:

- **Hyper-local information** relevant to immediate area
- **Time-sensitive content** that needs offline access
- **Community organizing** where internet access might be limited
- **Emergency information** when networks might be down
- **Fun and Interesting Information** when you just want to share something cool and unique.

---

**Need help?** Check the existing example files for complete working examples of each theme and feature.
